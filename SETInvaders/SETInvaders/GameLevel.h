/*
*	FILE		  : GameLevel.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the GameLevel class
*/

#pragma once
#include "Graphics.h"
#include "BitmapImage.h"
#include "BitmapObject.h"
#include "Obstacle.h"
#include "Enemy.h"
#include "Defender.h"
#include "Common.h"
#include "LevelGrid.h"


/**
 * \brief This is the root object for the game level. It contans all the objects for the level, 
 * including the sprites, the graphics controller, and the level settings. It contains its own
 * functionality to render, update and reset the level
 */
class GameLevel
{
protected:
	float ySpeed{};
	BitmapObject* backDrop{};
	Obstacle** obstacles;
	Enemy* enemy{};
	Defender* defender;
	std::vector<GameObject*> sprites;
	LevelGrid* gameGrid;
	Graphics* gfx;
	int numberOfObstacles;
	float renderWidth{};
	float renderHeight{};
	float obstacleScale;
	float enemyScale;
	float enemySpeed;
	int columns;
	int rows;
	bool tileBackground;
	static int ticks;
	int numberOfEnemies;
	int numberOfDeadEnemies;

public:
	GameLevel(float obstacleScale, float enemyScale, float enemySpeed, int columns, int rows,
	          int numberOfObstacles, Graphics* graphics, bool tileBackground);
	virtual ~GameLevel() = kMAKE_VIRTUAL;
	virtual void Load() = kMAKE_VIRTUAL;
	virtual void Unload() = kMAKE_VIRTUAL;
	virtual void Update(int ticks) = kMAKE_VIRTUAL;
	virtual void Render() = kMAKE_VIRTUAL;
	virtual void ResetLevel() = kMAKE_VIRTUAL;
	virtual void CalculateHeight() = kMAKE_VIRTUAL;
	virtual void CalculateWidth() = kMAKE_VIRTUAL;
};
