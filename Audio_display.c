// 宏定义
#define LED_BASE 0xFF200000    
#define KEYs_BASE 0xff200050
#define Pixel_buffer_controlloer 0xFF203020
#define Edge_capture 0xff20005C
#define Switch_Base  0xFF200040 

// 添加库
#include <stdlib.h>
#include<stdio.h>
#include <stdbool.h>

// 指针定义
volatile unsigned int *led = (unsigned int*) LED_BASE;		      // LED基地址
volatile unsigned int *KEYs = (unsigned int *) KEYs_BASE;       // Key基地址
volatile unsigned int *edge_cap = (unsigned int *)Edge_capture; // 边缘检测器
volatile unsigned int *switch_Base = (unsigned int *) Switch_Base;//Switch基地址
volatile int pixel_buffer_start; // global variable
short int Buffer1[240][512];     // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];
int base[10] = {0xFFFF, 0xFFE0,  0xF800,  0x07E0, 0x001F, 0x07FF, 0xF81F, 0xC618, 0xFC18, 0xFC00}; 
// white, yellow, red, green, blue, cyan, magenta, grey, pink, orange



// 函数定义
void plot_pixel(int x, int y, short int line_color)
{
    volatile short int *one_pixel_address;
        one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
        *one_pixel_address = line_color;
}


void drawunit(int x, int y, int Box2[9][9]) {
  for (int a = 0; a < 9; a++) {
    for (int b = 0; b < 9; b++) {
      plot_pixel(x-4+a, y-4+b, Box2[a][b]);
    }
  }
}

void clear_screen()
{
  int x, y;
  for (x = 0; x < 320; x++)
          for (y = 0; y < 240; y++)
                  plot_pixel (x, y, 0);
}

void initialize_screen(int We1[240][320])
{
  int x, y;
  for (x = 0; x < 320; x++)
          for (y = 0; y < 240; y++)
                  plot_pixel (x, y, We1[y][x]);
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





int main(void)
{
  //double buffer
  volatile int * pixel_ctrl_ptr = (int *)Pixel_buffer_controlloer;  // Read location of the pixel buffer from the pixel buffer controller
  /* set front pixel buffer to Buffer 1 */
  *(pixel_ctrl_ptr + 1) = (int)&Buffer1;  // first store the address in the  back buffer
  /* now, swap the front/back buffers, to set the front buffer location */
  wait_for_vsync();
  /* initialize a pointer to the pixel buffer, used by drawing functions */
  pixel_buffer_start = *pixel_ctrl_ptr;
  clear_screen();  // pixel_buffer_start points to the pixel buffer
  /* set back pixel buffer to Buffer 2 */
  *(pixel_ctrl_ptr + 1) = (int)&Buffer2;
  pixel_buffer_start = *(pixel_ctrl_ptr + 1);  // we draw on the back buffer
  clear_screen();  // pixel_buffer_start points to the pixel buffer

  while (1) {
  clear_screen();
  audio_playback_mono(samples, samples_n);
  wait_for_vsync();  // swap front and back buffers on VGA vertical sync
  pixel_buffer_start = *(pixel_ctrl_ptr + 1);  // new back buffer
  }
}




