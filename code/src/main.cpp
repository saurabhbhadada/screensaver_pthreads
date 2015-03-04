#include <GL/glut.h>  
#include <cmath>    
#define PI 3.14159265f
#include <cstdlib>
#include<iostream>
#include<vector>
#include<pthread.h>
#include<map>
#include<utility>
#include "../obj/shapes.h"
#include "../obj/collision.h"
#include "../obj/Grid.h"
#include "../obj/physics.h"
using namespace std; 

int windowWidth  = 700;     
int windowHeight = 700;     
int windowPosX   = 0;      
int windowPosY   = 0;      
int refresh = 30; // in miliseconds

bool fullScreenMode = true;

GLfloat clipXleft   = -350.0;
GLfloat clipXright  = 350.0;
GLfloat clipYbottom = -350.0;
GLfloat clipYtop    = 350.0;

int no_of_balls;
vector<Ball> bls;

Grid GRID(clipXright-clipXleft,clipYtop-clipYbottom,20.0);

multimap<int,int> gmap;
pthread_mutex_t mut_map;

pthread_barrier_t barrier;

void createBalls(){
	GLfloat rad,blxmi,blxma,blymi,blyma,x_position,y_position,x_velocity,y_velocity;
	float range_x,range_y;
	for(int i=0;i<no_of_balls;i++){
		int b_no = i;
		GLfloat rad=5.0f+static_cast <float> (rand())/(static_cast <float> (RAND_MAX/10.0));		
		GLfloat blxmi=clipXleft+rad;
		GLfloat blxma=clipXright-rad;
		GLfloat blymi=clipYbottom+rad;
		GLfloat blyma=clipYtop-rad;
		float range_x = blxma-blxmi;
		float range_y = blyma-blymi;
	
		GLfloat x_position=blxmi+ static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/range_x));
		GLfloat y_position=blymi+ static_cast <float> (rand())/ (static_cast <float> (RAND_MAX/range_y));
		GLfloat x_velocity = -5.0+ static_cast <float> (rand())/(static_cast <float> (RAND_MAX/10.0));
		GLfloat y_velocity = -5.0+ static_cast <float> (rand())/(static_cast <float> (RAND_MAX/10.0));
		Ball b1(b_no,x_position,y_position,rad,x_velocity,y_velocity,blxmi,blxma,blymi,blyma);
		bls.push_back(b1);
		
	}
}
void *routine(void *id){
long i1 = (long) id;
bls[i1].updateBall();

//shift to top corner
GLfloat x_pos_shifted=bls[i1].x_position-clipXleft;
GLfloat y_pos_shifted=bls[i1].y_position-clipYtop;          
int grid_bx_no = (int)(floor(abs(x_pos_shifted)/GRID.cellSize) + (floor(abs(y_pos_shifted)/GRID.cellSize)*(GRID.cols)));
pthread_mutex_lock(&mut_map);
gmap.insert(pair<int, int>(grid_bx_no,i1));
pthread_mutex_unlock(&mut_map);
pthread_barrier_wait(&barrier);
collision coll;
physics phy;

int offsts[9];
offsts[0]=0;
offsts[1]=1;
offsts[2]=-1;
offsts[3]=GRID.cols;
offsts[4]=GRID.cols+1;
offsts[5]=GRID.cols-1;
offsts[6]=-GRID.cols;
offsts[7]=-GRID.cols+1;
offsts[8]=-GRID.cols-1;

int itr;
int gnb_off;
int flag1;
for(int itr=0;itr<9;itr++){
	flag1=0;
	gnb_off = grid_bx_no+offsts[itr];	
	if(grid_bx_no%GRID.cols!=0 && grid_bx_no%GRID.cols!=GRID.cols){
		if(gnb_off>=0 && gnb_off<GRID.gridSize){
			flag1=1;			
		}		
	}
	else{
		if(grid_bx_no%GRID.cols==0){
			if(gnb_off>=0 && gnb_off<GRID.gridSize){
				if(itr!=2 && itr!=5 && itr!=8){
					flag1=1;				
				}			
			}
		}
		else if(grid_bx_no%GRID.cols==GRID.cols-1){
			if(gnb_off>=0 && gnb_off<GRID.gridSize){
				if(itr!=1 && itr!=4 && itr!=7){
					flag1=1;				
				} 			
			}		
		}
	}
	if(flag1){
		pair<multimap<int,int>::iterator, multimap<int,int>::iterator> pif;
		pif=gmap.equal_range(gnb_off);
		for(multimap<int,int>::iterator it1=pif.first;it1!=pif.second;++it1){
		        int i2=(*it1).second;
                        if(i1!=i2){
                                if(coll.chkCollision(&bls[i1],&bls[i2])){
			                phy.collisionBall(&bls[i1],&bls[i2]);
			                pthread_mutex_lock(&bls[i1].mutex_edit);
			                pthread_mutex_lock(&bls[i2].mutex_edit);
			                bls[i1].x_velocity=phy.xv1;
			                bls[i1].y_velocity=phy.yv1;
			                bls[i2].x_velocity=phy.xv2;
			                bls[i2].y_velocity=phy.yv2;
			                bls[i1].x_position=phy.x1;
			                bls[i2].y_position=phy.y1;
			                bls[i2].x_position=phy.x2;
			                bls[i2].y_position=phy.y2;
			                pthread_mutex_unlock(&bls[i2].mutex_edit);
			                pthread_mutex_unlock(&bls[i1].mutex_edit);		
		                }
                        }
                        		
		} 	
	}
}
/*
for(int i2=i1;i2<no_of_balls;i2++){
	if(i2!=i1){
		if(coll.chkCollision(&bls[i1],&bls[i2])){
			phy.collisionBall(&bls[i1],&bls[i2]);
			pthread_mutex_lock(&bls[i1].mutex_edit);
			pthread_mutex_lock(&bls[i2].mutex_edit);
			bls[i1].x_velocity=phy.xv1;
			bls[i1].y_velocity=phy.yv1;
			bls[i2].x_velocity=phy.xv2;
			bls[i2].y_velocity=phy.yv2;
			bls[i1].x_position=phy.x1;
			bls[i2].y_position=phy.y1;
			bls[i2].x_position=phy.x2;
			bls[i2].y_position=phy.y2;
			pthread_mutex_unlock(&bls[i2].mutex_edit);
			pthread_mutex_unlock(&bls[i1].mutex_edit);		
		}			
	}
}*/
coll.CollisionWall(&bls[i1]);
} 






void display(){
glClear(GL_COLOR_BUFFER_BIT);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
int vec_size = bls.size();
for(int i=0;i<vec_size;i++){
	bls[i].DrawCircle();
}

glutSwapBuffers();

pthread_t threads[no_of_balls];
int rc=0;
void *status;
pthread_barrier_init(&barrier,NULL,no_of_balls);
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
pthread_mutex_init(&mut_map,NULL);

for(int i=0;i<vec_size;i++){
	bls[i].initMutex();
	rc=pthread_create(&threads[i],&attr,routine,(void *)i);	

	if(rc){
		cout<<"ERRor"<<rc;
		exit(-1);
	}
}

pthread_attr_destroy(&attr);

for(int i=0;i<vec_size;i++){
	bls[i].destroyMutex();
	pthread_join(threads[i],&status);
}
pthread_mutex_destroy(&mut_map);

}





void initGL(){
glClearColor(1.0f,1.0f,1.0f,1.0f);
}



void Timer(int value) {
   glutPostRedisplay();    
   glutTimerFunc(refresh, Timer, 0); 
}



void reshape(GLsizei width, GLsizei height) {
   
   if (height == 0) height = 1;                
   GLfloat aspct = (GLfloat)width / (GLfloat)height;
 
   glViewport(0, 0, width, height);
   //windowWidth  = (int) width;     
   //windowHeight = (int) height;
  
   glMatrixMode(GL_PROJECTION);  
   glLoadIdentity(); 	

   if (width >= height) {
      clipXleft   = -350.0 * aspct;
      clipXright  = 350.0 * aspct;
      clipYbottom = -350.0;
      clipYtop    = 350.0;
   } else {
      clipXleft  = -350.0;
      clipXright  = 350.0;
      clipYbottom = -350.0 / aspct;
      clipYtop    = 350.0 / aspct;		   
   }
   gluOrtho2D(clipXleft, clipXright, clipYbottom, clipYtop);
   for(int z=0;z<no_of_balls;z++){
	bls[z].ballXmin=clipXleft+bls[z].radius;
	bls[z].ballXmax=clipXright-bls[z].radius;
	bls[z].ballYmin=clipYbottom+bls[z].radius;
	bls[z].ballYmax=clipYtop-bls[z].radius;		
   }	

}

void keyboard(unsigned char key,int x,int y){
	
	for(int i=0;i<no_of_balls;i++){
		bls[i].board(key,x,y);
	}	
	
}


void specialKeys(int key,int x,int y)
{
	bls[0].keys(key,x,y);		
	
}

void mouse(int button,int state,int x,int y)
{
	for(int i=0;i<no_of_balls;i++){
		bls[i].pause(button,state,x,y);
	}
	
}

int main(int argc, char* argv[]) {
   if ( argc > 1 ) {
    no_of_balls = atoi( argv[1] );
   }
   glutInit(&argc, argv);            
   glutInitDisplayMode(GLUT_DOUBLE); 
   glutInitWindowSize(windowWidth, windowHeight);  
   glutInitWindowPosition(windowPosX, windowPosY); 
   glutCreateWindow("ScreenSaver"); 
   
   
   createBalls();     
   glutDisplayFunc(display);    
   glutReshapeFunc(reshape);     
   glutTimerFunc(0, Timer, 0); 
   glutSpecialFunc(specialKeys);
   glutKeyboardFunc(keyboard);
   glutFullScreen();
   glutMouseFunc(mouse);  
   initGL();                     
   glutMainLoop();               
   return 0;
}
