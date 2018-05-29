/*
*	FILE		  : Enemy.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the Enemy class
*/

#pragma once
#include "BitmapObject.h"
#include "LevelGrid.h"
#define kNUMBER_OF_ENEMY_FILES 4
/**
 * \brief This class reprents an enemy in the game. The enemy is a renderable object that is dynamically
 * drawn to the screen. This class controls the horizontal and vertical speeds
 */
class Enemy : public BitmapObject
{
	float xSpeed;
	float ySpeed;
	std::vector<BitmapImage*> images;
public:
	Enemy();
	Enemy(BitmapImage* graphics);
	Enemy(std::vector<BitmapImage*> graphics);
	Enemy(float x, float y, BitmapImage* image);
	Enemy(float x, float y, std::vector<BitmapImage*> graphics);
	~Enemy();
	bool SetXSpeed(float xSpeed);
	float GetXSpeed();
	bool SetYSpeed(float ySpeed);
	float GetYSpeed();
	bool AddImage(BitmapImage* graphics);
	std::vector<BitmapImage*> GetImages();
	bool Draw(float gameW, float gameH, int gridXScale, int gridYScale, float scale, int imageIndex);
	bool Move(LevelGrid* grid, float gameWidth, float gameHeight);
	bool ChangeImage(int imageIndex);
};
