#include<vector>
#include<cmath>
#include<cstdlib>
using namespace std;
class Grid {
	public:
		float cellSize;
		int cols;
		int rows;
		int gridSize;
		//vector< vector<int> > grid;
		Grid(float w,float h, float cs);
		//void Add(int b_no,float x_p,float y_p); 
};

Grid::Grid(float w,float h,float cs){
	cellSize = cs;
	cols = (int) (w/cellSize);
	rows = (int) (h/cellSize);
	gridSize=cols*rows;
};
/*
void Grid::Add(int b_no,float x_p,float y_p){
	int grid_bx_no = (int)(Math.floor(x_p/cellSize) + (Math.floor(y_p/cellSize)*cols)
	grid[grid_bx_no].push_back(b_no);
};
*/
