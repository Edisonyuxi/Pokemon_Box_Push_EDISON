# Pokemon_Box_Push_EDISON
A Box Pushing Game using DEI-SOC

Author：Yuxi Zhang(edisonyuxi.zhang@mail.utoronto.ca), Olivia Zhang(oliviayubin.zhang@mail.utoronto.ca)
# Project Introduction 
This project aims at building a box pushing game that has four elements: Robot, Boxes, Highlighted 
Areas and Walls. Users will use PS2 keyboard to control the Robot to push boxes to cover all 
highlighted areas. Game is over if the robot successfully moves all boxes onto the highlighted areas, 
or the boxes get stuck and can’t move anymore. VGA Displays are used to display the game maps 
and audios are implemented to indicate the game status. Users can also use Keys & Switches to 
reset/return to the Welcome page/choose the difficulty level of the game. 

# Implementation Process:
1. Game Logic Development: Design box pushing logic, including robot control, movement 
assessment, drawing logic, and end-game conditions.
2. Game State Development：Establish game states: Welcome, Start, End, and Reset, along with 
varying difficulty levels. Design control methods using switches and keys.
3. Animation making: implement draw functions to create smooth and excellent animation during 
state transitions.
4. User interface design: Utilize Procreate and Pixiart for designing the welcome and ending 
pages, and for creating visually appealing game element images.
5. PS/2 Keyboard implementation: implement a PS2 keyboard interface, enabling users to use 
WASD keys to control the robot. 
Audio implementation: Record and implement suitable audios to indicate the Game statuses.
6. Functionality Testing: Conduct multiple tests to improve the smoothness and playability of the 
game, ensuring every function operates correctly.

![image](https://github.com/user-attachments/assets/5e1752d9-dd30-490f-b777-c6a9a99c094c)
# Game Logics
1. There are four types of block: Robot, Walls, Boxes and the highlighted areas.
2. Robot is controlled by the player with WASD. Users can use the robot to push box. robot can only push one box at one time.
3. Walls are used to determine the region of the box-pushing area. Robot can't go onto the wall blocks, and Boxes also can't be pushed onto the Wall blocks.
4. If the robot is carrying a box, the other boxes will be seen the same as the walls.
5. The robot can only push the box, but can't drag the box backward. So be careful when push the box towards the walls!
6. If all highlighted areas are covered by the box, then the player win the game.

# Game States
1. The total state of the game is: Welcome, End, Reset and different game level states.
2. There are 10 game levels. Users will use the SW[0:9] on the FPGA(DEI_SOC) to control the game level. The diffculty level is accumalted from SW[0] to SW[9].
3. The robot are initialized in a sticked position from the VGA display axis (160, 166). In real games on the FPGA, users will use the PS2 keyboard to control the robot. When simulating in the CPUlator, we will use the KEY[0:3] as the WASD to control the robot.
4. When in the game, the player may fail(they can't move every box to the hightlighted area), they can press the reset button(SW[1] in CPUlator, KEY[0]) to reset the game status so they can have another chance.
5. When the player successfully push every box to the highlighted area, then the player win this game, there will be a switch to the end page.
6. When the player in the End page, KEY[0] can be used to return to the welcome page to have another game.

![e101c911d34f0ba6ecb34baa21fc548](https://github.com/user-attachments/assets/c9825412-22a1-4cc9-8645-2e5f1b403515)
![c2a49ff64e7c0c99933044ee08bb562](https://github.com/user-attachments/assets/49aac154-05f0-4f1e-891d-fe2b3ddcd7a1)
![f42a2005d04b9da54b0d3395bbbd536](https://github.com/user-attachments/assets/4e885f5c-8ab4-42f6-bbbf-9e42e9393164)
![e747d456c08ef7c2858eb8aec141ace](https://github.com/user-attachments/assets/a636e21d-4590-464f-8788-2213d72a2694)
![e747d456c08ef7c2858eb8aec141ace](https://github.com/user-attachments/assets/8961c4f0-cde8-4e3b-a2bc-1ed638a967bb)
![e747d456c08ef7c2858eb8aec141ace](https://github.com/user-attachments/assets/569b224f-9689-488f-ad94-d2f8c1754548)
![e747d456c08ef7c2858eb8aec141ace](https://github.com/user-attachments/assets/12e6f3c2-3bec-4c54-8084-1c4cf9955f91)



