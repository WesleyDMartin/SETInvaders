/*
*	FILE		  : LevelGrid.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the LevelGrid definition
*/

#include "LevelGrid.h"


/**
 * \brief The constructor for the level grid, sets up the grid
 * \param columns The column count of the grid
 * \param rows The row count of the grid
 */
LevelGrid::LevelGrid(int columns, int rows)
{
	this->columns = columns;
	this->rows = rows;

	// Reserve space for the grid
	grid = (int *)calloc(columns * rows, sizeof(int));
}



/**
 * \brief The destructor for grid leve, frees the grid
 */
LevelGrid::~LevelGrid()
{
	free(grid);
}



/**
 * \brief 
 * \param columns The new column count of the grid
 * \return 
 */
bool LevelGrid::setColumns(int columns)
{
	bool ret = true;
	this->columns = columns;
	return ret;
}



/**
 * \brief 
 * \param rows The new row count of the grid
 * \return 
 */
bool LevelGrid::setRows(int rows)
{
	bool ret = true;
	this->rows = rows;
	return ret;
}


/**
 * \brief Get the column count of the grid
 * \return The column count
 */
int LevelGrid::getColumns()
{
	return columns;
}


/**
* \brief Get the row count of the grid
* \return The row count
*/
int LevelGrid::getRows()
{
	return rows;
}



/**
 * \brief 
 * \param columns The new column count of the grid
 * \param rows The new row count of the grid
 * \return 
 */
bool LevelGrid::setDimensions(int columns, int rows)
{
	bool ret = true;
	this->columns = columns;
	this->rows = rows;
	return ret;
}



/**
 * \brief Fills the x and y parameters with the index of an empty slot in the grid
 * \param column (OUT) Stores the value of the found empty column
 * \param row (OUT) Stores the value of the found empty row
 * \return 
 */
bool LevelGrid::getEmptySlot(int* column, int* row, int highestRow = kUNDEFINED)
{
	if(highestRow == kUNDEFINED)
	{
		highestRow = this->rows;
	}

	bool ret = true;
	if (hasRoom())
	{
		do
		{
			*column = rand() % columns;
			*row = (rand() % (rows - highestRow + kFIX_OFF_BY_ONE_ERROR)) + highestRow - kFIX_OFF_BY_ONE_ERROR;
		}
		while (*(grid + (int)(*column + *row * columns)) != kBLOCK_IS_EMPTY);
	}
	else
	{
		*column = kDEFAULT;
		*row = kDEFAULT;
		ret = false;
	}

	return ret;
}



/**
 * \brief Checks to see if the grid has room available
 * \return Indicates if there is room in the grid
 */
bool LevelGrid::hasRoom(void)
{
	bool ret = false;
	for (int i = kDEFAULT; i < columns * rows; i++)
	{
		if (*(grid + i) == kBLOCK_IS_EMPTY)
		{
			ret = true;
		}
	}
	return ret;
}



/**
 * \brief Marks a slot on the grid as filled
 * \param column The column index to fill
 * \param row The row index to fill
 * \return Indicates if the slot was succesfully filled
 */
bool LevelGrid::fillSlot(int column, int row)
{
	bool ret = true;
	*(grid + (int)(column + row * columns)) = kBLOCK_IS_FULL;
	return ret;
}



/**
 * \brief Checks to see if a specific square is occupied
 * \param x The x coordinate to be checked
 * \param y The y coordinate to be looked at
 * \param gameW The width of the game area
 * \param gameH The height of the game area
 * \return Indicates if the square is occupied or not
 */
bool LevelGrid::isOccupied(int column, int row, int gameW, int gameH)
{
	bool ret = false;
	if (*(grid + (column * row + column)*4) == kBLOCK_IS_FULL)
	{
		ret = true;
	}
	return ret;
}



/**
 * \brief Clears the game grid
 * \return Status of clearing the grid
 */
bool LevelGrid::clearGrid()
{
	bool ret = true;
	memset(grid, kDEFAULT, columns * rows * sizeof(int));
	return ret;
}



/**
* \brief Converts an Y value into its relative row value
* \param y Value to convert to relative row
* \param gameH Width of the target render area
* \return
*/
int LevelGrid::RowFromY(int y, int gameH)
{
	return (int)ceil((y) / (gameH / rows));
}



/**
 * \brief Converts an X value into its relative column value
 * \param x Value to convert to relative column
 * \param gameW Width of the target render area
 * \return 
 */
int LevelGrid::ColumnFromX(int x, int gameW)
{
	return (int)ceil((x) / (gameW / columns));
}



/**
* \brief Converts a column to an Y value
* \param row Column to convert to Y
* \param gameH The height of the game render area
* \return
*/
float LevelGrid::YFromRow(int row, int gameH)
{
	return (float)row * ((float)gameH / (float)rows);
}

/**
 * \brief Converts a column to an X value
 * \param column Column to convert to X
 * \param gameW The width of the game render area
 * \return 
 */
float LevelGrid::XFromColumn(int column, int gameW)
{
	return (float)column * ((float)gameW / (float)columns);
}
