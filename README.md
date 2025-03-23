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
# Game States
1. The total state of the game is: Welcome, Start, End, Reset and different game level states.
2. There are 10 game levels. Users will use the SW[0:9] on the FPGA(DEI_SOC) to control the game level.
3. The robot are initialized in a sticked position from the VGA display axis (160.166). In real games on the FPGA, users will use the PS2 keyboard to control the robot. When simulating in the CPUlator, we will use the KEY[0:3] as the WASD to control the robot.
