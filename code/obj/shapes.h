#ifndef SHAPES_H
#define SHAPES_H
#include <GL/glut.h>  
#include <cmath>
#include <vector>
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
		bool fullScreenMode;
		bool paused;
		GLfloat c_r;
		GLfloat c_g;
		GLfloat c_b;
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

#endif //SHAPES_H
