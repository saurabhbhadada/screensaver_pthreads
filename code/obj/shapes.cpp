#include <GL/glut.h>  
#include <cmath>
#include <cstdlib>    
#include <iostream>
#include <vector>
#include<pthread.h>
#define PI 3.14159265f

class Ball
{
	public:
		int ball_no;
		GLfloat x_velocity;
		GLfloat y_velocity;
		//GLfloat time_elapsed = 0;
		GLfloat x_position;
		GLfloat y_position;
		GLfloat radius;
		GLfloat ballXmin;
		GLfloat ballXmax;
		GLfloat ballYmin;
		GLfloat ballYmax;
		int windowWidth;
		int windowHeight;
		int windowPosX;
		int windowPosY;
		GLfloat c_r;
		GLfloat c_g;
		GLfloat c_b;
		bool fullScreenMode;
		bool paused;
		GLfloat xSpeedSaved,ySpeedSaved;
		//vector<int> chk_collision_with;
		pthread_mutex_t mutex_edit;
		
		Ball(int bn,GLfloat x,GLfloat y,GLfloat r,GLfloat x_vel, GLfloat y_vel,GLfloat blxmi,GLfloat blxma,GLfloat blymi,GLfloat blyma );
		void DrawCircle();
		void updateBall();
		void initMutex();
		void destroyMutex();
		void board(unsigned char key,int x,int y);
		void keys(int key,int x,int y);
		void pause(int button,int state,int x,int y);
};

void Ball::DrawCircle()
{
	glPushMatrix(); 
	glTranslatef(x_position,y_position, 0.0);  
	glBegin(GL_TRIANGLE_FAN);	
	glColor3f(c_r,c_g,c_b);  
	glVertex2f(0.0f, 0.0f);       
	int numSegments = 200;
	GLfloat angle;
	for (int i = 0; i <= numSegments; i++) { 
	angle = i * 2.0f * PI / numSegments;
	glVertex2f(cos(angle) * radius, sin(angle) * radius);
	}
	glEnd();
	glPopMatrix();
};
Ball::Ball(int bn,GLfloat x,GLfloat y,GLfloat r,GLfloat x_vel, GLfloat y_vel,GLfloat blxmi,GLfloat blxma,GLfloat blymi,GLfloat blyma ){
	ball_no=bn;	
	radius = r;
	x_position = x;
	y_position = y;
	x_velocity=x_vel;
	y_velocity=y_vel;
	ballXmin=blxmi;
	ballXmax=blxma;
	ballYmin=blymi;
	ballYmax=blyma;
        windowWidth = 700;
	windowHeight = 700;
	windowPosX = 0;
	windowPosY = 0;
	fullScreenMode = true;
	paused = false;
	c_r=0.0f;
	c_g=0.0f;
	c_b=1.0f;
	//DrawCircle();
};
void Ball::initMutex(){
	pthread_mutex_init(&mutex_edit,NULL);	
}
void Ball::destroyMutex(){
	pthread_mutex_destroy(&mutex_edit);	
}
void Ball::updateBall(){
	x_position+=x_velocity;
	y_position+=y_velocity;
};

void Ball::board(unsigned char key,int x,int y){
	switch(key) {
		case 27:
			exit(0);
			break;
	}
};


void Ball::keys(int key,int x,int y)
{
	switch(key) {
		case GLUT_KEY_F1:
			fullScreenMode = !fullScreenMode;
			if(fullScreenMode){
				windowPosX = glutGet(GLUT_WINDOW_X);
				windowPosY = glutGet(GLUT_WINDOW_Y);
				windowWidth = glutGet(GLUT_WINDOW_WIDTH);
				windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
				glutFullScreen();
			} else {
				glutReshapeWindow(windowWidth,windowHeight);
				glutPositionWindow(windowPosX,windowPosY);
			}
			break;
		case GLUT_KEY_RIGHT:
			x_velocity += 0.5f;
			c_b=0.0f;
			c_r=1.0f;	
			break;
		case GLUT_KEY_LEFT:
			x_velocity -= 0.5f;
			c_b=0.0f;
			c_r=1.0f;
			break;
		case GLUT_KEY_UP:
			y_velocity += 0.5f;
			c_b=0.0f;
			c_r=1.0f;
			break;
		case GLUT_KEY_DOWN:
			y_velocity -= 0.5f;
			c_b=0.0f;
			c_r=1.0f;
			break;
	}
};

void Ball::pause(int button,int state,int x,int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		paused = !paused;
		if(paused)
		{
			xSpeedSaved = x_velocity;
			ySpeedSaved = y_velocity;
			x_velocity=0;
			y_velocity=0;
		} else {
			x_velocity = xSpeedSaved;
			y_velocity = ySpeedSaved;
		}
	}
};
