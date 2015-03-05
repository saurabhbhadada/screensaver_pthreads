# screensaver_pthreads
# this is a screensaver application made using C++, OpenGL, pthreads and works only on linux platform.
-----------------------------------------------------------------------------------------------------------------------------------------------
HOW TO USE

1. Open Terminal.
2. Change the directory to that of application folder.
3. Type the command "make execute num_thread=n". where n is number of balls in screensaver.
4. Mouse click on window toggles the state between pause and play.
5. Speed of red ball can be increased and decreased using arrow keys. 

-----------------------------------------------------------------------------------------------------------------------------------------------

ABOUT THE SCREENSAVER:

This screesaver program displays the collission of N balls on the screen. Each of the ball initialises in a random position on the screen with some random velocity. The balls then undergo continous collissions with each other and the wall in an elastic manner in a gravity free environment. There are provisions to increase and decrease the speed of the balls, and also to pause the program if needed.

-----------------------------------------------------------------------------------------------------------------------------------------------
ABOUT THE CODE:

This program is developed using C++ in ubuntu environment. It can be used in any machine which uses the ubuntu operating system. OpenGL is used to implement the User interface.
The motion of the each ball is managed by one thread. For this purpose, pthreads are used. The threads then communicate with one another for determining their collissions. This syncronisation is done using mutex and barriers.
Spatial hashing is used in the source code for decreasing time complexity. Because of spatial hashing, each thread only needs to communicate with its nearby threads instead of communicating with each and every ball on the screen.

-----------------------------------------------------------------------------------------------------------------------------------------------

USER INTERFACE:

The speed of the balls can be increased or decreased using arrow keys on the keyboard. The screensaver can be paused and resumed using either spacebar or by left mouse click.

-----------------------------------------------------------------------------------------------------------------------------------------------
