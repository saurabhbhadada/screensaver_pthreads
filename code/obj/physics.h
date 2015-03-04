#include<GL/glut.h>
#include "shapes.h"
#include<cmath>  
class physics{
	public:
		GLfloat xv1;
		GLfloat xv2;
		GLfloat yv1;
		GLfloat yv2;
		GLfloat x1;
		GLfloat y1;
		GLfloat x2;
		GLfloat y2;
		void collisionBall(Ball*,Ball*);
};

