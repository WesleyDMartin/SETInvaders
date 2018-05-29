/*
*	FILE		  : Level1.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the Level1 class
*/

#pragma once
#include "GameLevel.h"
#include <ctime>

/**
 * \brief This represents a level one object in the game. It likely will need to be generalized for 
 * a non specific level, but currently it is used to create the only level in the game
 */
class Level1 : public GameLevel
{
public:
	Level1(float obstacleScale, float enemyScale, float enemySpeed, int columns, int rows, int numberOfObstacles,
	       Graphics* graphics, bool tileBackground);
	void Load() override;
	void Unload() override;
	void Update(int ticks) override;
	void Render() override;
	void ResetLevel() override;
	void CalculateHeight() override;
	void CalculateWidth() override;
	Graphics* GetGraphics();
};
