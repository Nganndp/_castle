#pragma once
#include <vector>
#include "GameObject.h"
#include <set>
#include "define.h"

#define CELL_WIDTH 80  //320/4
#define CELL_HEIGHT 60  //240/4

//each cell in grid = 1/16 screen

using namespace std;

class Grid
{
public:

	Grid() 
	{ 
	}
	int maprow, mapcol;

	void InsertIntoGrid(CGameObject *object, int rowstart, int colstart, int rowend, int colend);
	void CheckSimonRevive(bool isRevive);

	void GetListCollisionFromGrid(Camera * Camera, vector<CGameObject*> &listColObjects);
	void TakeObjectsFromCell(int rowIndex, int colIndex, vector<CGameObject*> &listColObjects);
	void ClearGrid();
	~Grid();
	
private:

	vector<LPGAMEOBJECT> cells[200][200];
	set<CGameObject*> listTemp1;  //set: tồn tại 1 object duy nhất đó và ko trùng
	int rowstart, rowend, colstart, colend, rowIndex, colIndex;
	bool isRevive = false;
};

