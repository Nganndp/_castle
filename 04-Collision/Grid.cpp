#include "Grid.h"

void Grid::InsertIntoGrid(CGameObject * object, int rowstart, int colstart, int rowend, int colend)
{
	this->rowstart = rowstart;
	this->rowend = rowend;
	this->colstart = colstart;
	this->colend = colend;
	for (int i = this->rowstart; i <= this->rowend; i++)
	{
	   for (int j = this->colstart; j <= this->colend; j++)
	   {
		   cells[i][j].push_back(object);
	   }
	}
}

void Grid::ClearGrid()
{
	for (int i = 0; i <= maprow ;++i)
	{
		for (int j = 0; j <= mapcol; ++j)
		{
			cells[i][j].clear();
		}
	}
}

void Grid::GetListCollisionFromGrid(Camera * Camera, vector<CGameObject*>& listColObjects)
{
	int rowCam = (Camera->GetPosition().y) / (CELL_HEIGHT);
	int colCam = (Camera->GetPosition().x) / (CELL_WIDTH);

	listColObjects.clear();
	listTemp1.clear();



	for (int j = 0; j <= (SCREEN_HEIGHT-15) / CELL_HEIGHT; j++)
	{
		for (int i = 0; i <= SCREEN_WIDTH / CELL_WIDTH; i++)
		{
			TakeObjectsFromCell(j + rowCam, i + colCam, listColObjects);

		}
	}

}

void Grid::TakeObjectsFromCell(int rowIndex, int colIndex, vector<CGameObject*>& listColObjects)
{
	for (int i = 0; i < cells[rowIndex][colIndex].size(); i++)
	{
		if (cells[rowIndex][colIndex].at(i)->GetActive() == true)
		{
			if (listTemp1.find(cells[rowIndex][colIndex].at(i)) == listTemp1.end())
			{
				listTemp1.insert(cells[rowIndex][colIndex].at(i));
				listColObjects.push_back(cells[rowIndex][colIndex].at(i));
			}
		}

	}
}



Grid::~Grid()
{
}
