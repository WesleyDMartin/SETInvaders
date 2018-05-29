/*
*	FILE		  : GameController.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the GameController class
*/

#pragma once

#include "GameLevel.h"

/**
 * \brief This is a singleton class that is used to control the game. It can switch 
 * and create new levels, and is used to render and update the game
 */
class GameController
{
	GameController() = default;
	static int previousTick;
	static GameLevel* currentLevel;
public:
	static bool Loading;
	static void Init();
	static void LoadInitialLevel(GameLevel* lev);
	static void SwitchLevel(GameLevel* lev);
	static void Render();
	static void Update();
	static int GetGameTicks();
};
