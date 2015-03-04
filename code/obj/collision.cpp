#include <GL/glut.h>  
#include "shapes.h"
#include <cstdlib> 
class collision{
	public:	
		void CollisionWall(Ball* b);
		int chkCollision(Ball* b1,Ball* b2);
};

void collision::CollisionWall(Ball* b){
	if (b->x_position > b->ballXmax) {
	      b->x_position = b->ballXmax;
	      b->x_velocity = -b->x_velocity;
	} else if (b->x_position < b->ballXmin) {
	      b->x_position = b->ballXmin;
	      b->x_velocity = -b->x_velocity;
	}
	if (b->y_position > b->ballYmax) {
	      b->y_position = b->ballYmax;
	      b->y_velocity = -b->y_velocity;
	} else if (b->y_position < b->ballYmin) {
	      b->y_position = b->ballYmin;
	      b->y_velocity = -b->y_velocity;
	}
};

int collision::chkCollision(Ball *b1,Ball *b2){
	float xx=(b1->x_position)-(b2->x_position);
	float yy=(b1->y_position)-(b2->y_position);
	if((xx*xx)+(yy*yy)>(b1->radius+b2->radius)*(b1->radius+b2->radius)){
		return 0;	
	}		
	else{
		return 1;	
	}
};

