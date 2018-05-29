/*
*	FILE		  : GameLevel.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the method declarations for the GameLevel class
*/

#include "GameLevel.h"


/**
 * \brief Constructs a new game level and prepares all the objects for that level
 * \param obstacleScale The scale of the obstacles
 * \param enemyScale The scale of the enemy 
 * \param enemySpeed The speed of the enemy
 * \param columns The number of columns
 * \param rows The number of rows
 * \param numberOfObstacles The number of obstacles
 * \param graphics The graphics driver to use
 * \param tileBackground Indicates if the background should be tiled or not
 */
GameLevel::GameLevel(float obstacleScale, float enemyScale, float enemySpeed, int columns, int rows,
                     int numberOfObstacles, Graphics* graphics, bool tileBackground)
{
	this->tileBackground = tileBackground;
	this->obstacleScale = obstacleScale;
	this->enemyScale = enemyScale;
	this->enemySpeed = enemySpeed;
	this->columns = columns;
	this->rows = rows;
	this->numberOfObstacles = numberOfObstacles;
	this->gfx = graphics;
	this->numberOfDeadEnemies = kDEFAULT;
	this->numberOfEnemies = kDEFAULT;
	obstacles = (Obstacle **)malloc(this->numberOfObstacles * sizeof(Obstacle*));
	gameGrid = new LevelGrid(this->columns, this->rows);
}



/**
 * \brief The destructor for this game level
 */
GameLevel::~GameLevel()
{
	free(gameGrid);
	free(obstacles);
}
