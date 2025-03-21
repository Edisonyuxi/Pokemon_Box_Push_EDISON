// 宏定义
#define LED_BASE 0xFF200000    
#define KEYs_BASE 0xff200050
#define Pixel_buffer_controlloer 0xFF203020
#define Edge_capture 0xff20005C

// 添加库
#include <stdlib.h>
#include<stdio.h>
#include <stdbool.h>

// 指针定义
volatile unsigned int *led = (unsigned int*) LED_BASE;		      // LED基地址
volatile unsigned int *KEYs = (unsigned int *) KEYs_BASE;       // Key基地址
volatile unsigned int *edge_cap = (unsigned int *)Edge_capture; // 边缘检测器
volatile int pixel_buffer_start; // global variable
short int Buffer1[240][512];     // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];
int base[10] = {0xFFFF, 0xFFE0,  0xF800,  0x07E0, 0x001F, 0x07FF, 0xF81F, 0xC618, 0xFC18, 0xFC00}; 
// white, yellow, red, green, blue, cyan, magenta, grey, pink, orange

// struct定义
struct Robot{
  int x;
  int y;
  int direction;
};

struct Box{
  int x;
  int y;
};

struct Wall{
  int x;
  int y;
};

struct hilight_area{
  int x;
  int y;
};


// 函数定义
void plot_pixel(int x, int y, short int line_color)
{
    volatile short int *one_pixel_address;
        one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
        *one_pixel_address = line_color;
}

void drawunit(int x, int y, int color) {
  for (int a = 0; a < 9; a++) {
    for (int b = 0; b < 9; b++) {
      plot_pixel(x-4+a, y-4+b, color);
    }
  }
}

void draw_verticalline(int x, int y, int color){
    for(int i=0;i<5;i++){
        drawunit(x,y+9*i,color);
    }
}

void draw_horizontalline(int x, int y, int color){
    for(int i=0;i<4;i++){
        drawunit(x+9*i,y,color);
    }
}

void welcome_Page(){
    draw_verticalline(133-9*11,120-9*10,0x07FF);
    draw_horizontalline(133-9*11,120-9*8,0x07FF);
    draw_verticalline(133-9*8,120-9*10,0x07FF);
    draw_verticalline(133-9*5,120-9*10,0x07FF);
    draw_horizontalline(133-9*5,120-9*10,0x07FF);
    draw_horizontalline(133-9*5,120-9*8,0x07FF);
    draw_horizontalline(133-9*5,120-9*6,0x07FF);
    draw_verticalline(133-9*-1,120-9*10,0x07FF);
    draw_verticalline(133-9*-4,120-9*10,0x07FF);
    draw_verticalline(133-9*-7,120-9*10,0x07FF);
    draw_horizontalline(133-9*-7,120-9*10,0x07FF);
    draw_horizontalline(133-9*-7,120-9*6,0x07FF);
    draw_verticalline(133-9*-10,120-9*10,0x07FF);
    draw_verticalline(133-9*-13,120-9*10,0x07FF);
    drawunit(133-9*-13,120-9*7,0x0000);
}

void draw_left_diagonal(int x, int y, int color){
    for(int i=0;i<7;i++){
        drawunit(x+9*i,y-9*i,color);
    }
}

void draw_right_diagonal(int x, int y, int color){
    for(int i=0;i<7;i++){
        drawunit(x+9*i,y+9*i,color);
    }
}

void End_Page(){
	draw_left_diagonal(133-9*12, 120-9*4, 0x07FF);
	draw_right_diagonal(133-9*6, 120-9*10, 0x07FF);
	draw_left_diagonal(133+9*6, 120-9*4, 0x07FF);
	draw_right_diagonal(133+9*12, 120-9*10, 0x07FF);
	draw_right_diagonal(133-9*3, 120+9*4, 0x07FF);
	draw_left_diagonal(133+9*3, 120+9*10, 0x07FF);
}


void drawRobot(int x, int y, int color) {
  for (int a = 0; a < 9; a++) {
    for (int b = 0; b < 9; b++) {
      plot_pixel(x-4+a, y-4+b, color);
    }
  }
}

void drawBox(struct Box boxlist[3]) {
  for(int i=0; i<3; i++){
    if(boxlist[i].x!=0 || boxlist[i].y!=0){
      drawunit(boxlist[i].x, boxlist[i].y,0x001F);
    }
  }
}

void drawarea(struct hilight_area arealist[3]) {
  for(int i=0; i<3; i++){
    drawunit(arealist[i].x, arealist[i].y,0xFFE0);
  }
}

void clear_screen()
{
  int x, y;
  for (x = 0; x < 320; x++)
          for (y = 0; y < 240; y++)
                  plot_pixel (x, y, 0);
}

void initialize_screen()
{
  int x, y;
  for (x = 0; x < 320; x++)
          for (y = 0; y < 240; y++)
                  plot_pixel (x, y, 0xFFFF);
}

void wait_for_vsync()
{
volatile int * pixel_ctrl_ptr = (int *) 0xff203020; // base address
int status;
*pixel_ctrl_ptr = 1;        // start the synchronization process- write 1 into front buffer address register
status = *(pixel_ctrl_ptr + 3); // read the status register
while ((status & 0x01) != 0) // polling loop waiting for S bit to go to 0
  {
  status = *(pixel_ctrl_ptr + 3);
  }
}


bool check_pixel(int x, int y, short int color1)
{
  volatile short int *pixel_address;
  pixel_address = (short int *)(pixel_buffer_start + (y << 10) + (x << 1));
  return *pixel_address == color1;
}

void delay(int seconds) {
    int delay_loops = (seconds * 100000000) / 10;
    for(int i = 0; i < delay_loops; i++) {
    }
}


int main(void) {
    volatile int * pixel_ctrl_ptr = (int *)Pixel_buffer_controlloer;
    /* set front pixel buffer to Buffer 1 */
    *(pixel_ctrl_ptr + 1) = (int)&Buffer1;
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();  // pixel_buffer_start points to the pixel buffer

    /* set back pixel buffer to Buffer 2 */
    *(pixel_ctrl_ptr + 1) = (int)&Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);  // we draw on the back buffer
    clear_screen();  // pixel_buffer_start points to the pixel buffer

    int boxX1 = 9, boxY1 = 120; 
    int boxX2 = 350; 

    while (1) {
        draw_left_diagonal(133-9*12, 120-9*4, 0x07FF);
        draw_right_diagonal(133-9*6, 120-9*10, 0x07FF);
        draw_left_diagonal(133+9*6, 120-9*4, 0x07FF);
        draw_right_diagonal(133+9*12, 120-9*10, 0x07FF);
        draw_right_diagonal(133-9*3, 120+9*4, 0x07FF);
        draw_left_diagonal(133+9*3, 120+9*10, 0x07FF);

		// 移动方块之前先清除旧位置
		if (boxX1 <= boxX2) {
			drawunit(boxX1, boxY1, 0x07FF);
			boxX1++;
		}
        wait_for_vsync();
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // 切换缓冲区
    }

}

