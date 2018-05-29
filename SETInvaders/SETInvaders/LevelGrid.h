/*
*	FILE		  : LevelGrid.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the LevelGrid class
*/

#pragma once
#include "Common.h"
#include "GameObject.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

/**
 * \brief This is the basic game grid for all levels. It contains a grid that tracks
 * where all objects are in the game. It has basic abilities such as clearing the grid, 
 * filling slots, and checking for empty space or the occupied status of slots
 */
class LevelGrid
{
	int columns;
	int rows;
	int* grid;

public:
	LevelGrid(int columns, int rows);
	~LevelGrid();
	bool setColumns(int columns);
	bool setRows(int rows);
	int getColumns();
	int getRows();
	bool setDimensions(int columns, int rows);
	bool getEmptySlot(int* column, int* row, int highestRow);
	bool hasRoom(void);
	bool fillSlot(int column, int row);
	bool isOccupied(int column, int row, int gameW, int gameH);
	bool clearGrid();
	int RowFromY(int y, int gameH);
	int ColumnFromX(int x, int gameW);
	float YFromRow(int row, int gameH);
	float XFromColumn(int column, int gameW);
};
