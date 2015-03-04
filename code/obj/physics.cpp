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
		void collisionBall(Ball* b1,Ball* b2);
};

void physics::collisionBall(Ball* b1,Ball* b2){
	GLfloat xd=b2->x_position-b1->x_position;
	GLfloat yd=b2->y_position-b1->y_position;
	GLfloat ang= atan(yd/xd);
	x1=b1->x_position;
	y1=b1->y_position;
	x2=b2->x_position;
	y2=b2->y_position;
	if(x1>x2){
		x1+=((b1->radius+b2->radius)*cos(ang))/8;
		x2-=((b1->radius+b2->radius)*cos(ang))/8;	
	}
	else{
		x2+=((b1->radius+b2->radius)*cos(ang))/8;
		x1-=((b1->radius+b2->radius)*cos(ang))/8;	
	}
	
	if(y1>y2){
		y1+=((b1->radius+b2->radius)*sin(ang))/8;
		y2-=((b1->radius+b2->radius)*sin(ang))/8;	
	}
	else{
		y2+=((b1->radius+b2->radius)*sin(ang))/8;
		y1-=((b1->radius+b2->radius)*sin(ang))/8;	
	}
	GLfloat ux1=b1->x_velocity;
	GLfloat uy1=b1->y_velocity;
	GLfloat ux2=b2->x_velocity;
	GLfloat uy2=b2->y_velocity;
	GLfloat r12=(b1->radius*b1->radius);
	GLfloat r22=(b2->radius*b2->radius);
	xv1=(ux1*cos(ang))+(uy1*sin(ang));
	yv1=(uy1*cos(ang))-(ux1*sin(ang));
	xv2=(ux2*cos(ang))+(uy2*sin(ang));
	yv2=(uy2*cos(ang))-(ux2*sin(ang));
	
	GLfloat temp1;
	GLfloat temp2;
	temp1=xv1;
	temp2=xv2;
	xv1=((temp1*(r12-r22))+(2.0*r22*temp2))/(r12+r22);
	xv2=((temp2*(r22-r12))+(2.0*r12*temp1))/(r12+r22);
	
	
	temp1 = xv1;
	temp2 = yv1;
	
	xv1=(temp1*cos(ang))-(temp2*sin(ang));
	yv1=(temp1*sin(ang))+(temp2*cos(ang));
	
	temp1 = xv2;
	temp2 = yv2;
	xv2=(temp1*cos(ang))-(temp2*sin(ang));
	yv2=(temp1*sin(ang))+(temp2*cos(ang));
	
};
