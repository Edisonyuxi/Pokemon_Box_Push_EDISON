# Pokemon_Box_Push_EDISON
A Box Pushing Game using DEI-SOC

Author：Yuxi Zhang(edisonyuxi.zhang@mail.utoronto.ca), Olivia Zhang(oliviayubin.zhang@mail.utoronto.ca)

(Do not copy the files for your academic work!)
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
![welcome_page](https://github.com/user-attachments/assets/573af2ad-a119-46cc-87a1-1a50d363e2aa)
![image](https://github.com/user-attachments/assets/30995cb0-d5ce-4a5b-8f8f-654c187ad54e)
![gamestate2](https://github.com/user-attachments/assets/e5680986-1472-41e1-ab74-4e01d0f2debe)
![gamestate3](https://github.com/user-attachments/assets/812a1f7a-d874-4bfe-ba5f-20eeaea75e92)
![gamestate4](https://github.com/user-attachments/assets/83f64aeb-7752-4423-adcf-c45ecabf773d)
![Endpage](https://github.com/user-attachments/assets/470572fd-eb4f-4735-8dd6-a19c49e819d3)
# Animation making
![Reset_ani](https://github.com/user-attachments/assets/3db1e85c-a1ab-4300-8f21-ebe12ed2a64e)
![ani2](https://github.com/user-attachments/assets/876278dd-97e0-4759-bc7d-37998475d70f)

The animations in our game are smooth and engaging. For example, when the user presses the reset button, a blue smiling face appears on the screen along with a dynamic loading bar that lasts about 4 seconds. This not only creates a visually appealing transition but also gives players a brief moment to rest and prepare for the next round.

The smoothness of the animation is largely attributed to the use of double buffering on the VGA display. Our implementation on the FPGA (DE1-SoC) uses the wait_for_sync function to synchronize buffer swapping. The switch between the front and back buffers occurs only after the back buffer has completed rendering, which effectively eliminates screen tearing and ensures a seamless visual experience  
# UI interface
# Audio display
# Functional testing
# Conclusion
Our project is a complete and successful design. We designed a smooth and playable box pushing game by implementing PS/2 Keyboard controls, audio playback, key and switch inputs, VGA Display, and PNG loading. The diverse of game states and the detail of the game logic add to the 
game's complexity, while the excellent animation and beautiful images contribute to a pleasant user interface. Through this project, we have deepened our understanding of this course's content and acquired new knowledge: how to convert PNG files to C arrays, how to convert audio files to C 
arrays, and most importantly, how to combine various functions to craft a complete game. There are still huge improvement space for our project, we will keep studying and trying to improve this game in future! Please feel free to contact if you are interested in creating the game with me!


