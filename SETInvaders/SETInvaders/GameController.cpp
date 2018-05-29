/*
*	FILE		  : GameController.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the method declarations for the GameController class
*/

#include "GameController.h"
#include <sys/timeb.h>

GameLevel* GameController::currentLevel;
bool GameController::Loading;
int GameController::previousTick = 0;


/**
 * \brief Initializes the game controller
 */
void GameController::Init()
{
	Loading = true;
	currentLevel = nullptr;
}



/**
 * \brief Load the initial level for the game
 * \param lev The first level of the game to be loaded
 */
void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true; //This can help us avoid loading activity while rendering
	previousTick = GetGameTicks();
	currentLevel = lev;
	currentLevel->Load();
	Loading = false;
}



/**
 * \brief Switch to a different level of the game
 * \param lev The current level of the game
 */
void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel->Unload();
	lev->Load();
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}



/**
 * \brief Renders or rerenders the game using current level render method
 */
void GameController::Render()
{
	if (Loading) return; //nice! Do not update or render if the scene is loading.
	currentLevel->Render();
}



/**
 * \brief Updates the status of the game, calls current level updater
 */
void GameController::Update()
{
	if (Loading || previousTick == GetGameTicks()) return; //nice! Do not update or render if the scene is loading.
	currentLevel->Update(GetGameTicks());
	previousTick = GetGameTicks();
}



/**
* \brief Gets the number of milliseconds that have passed
* \return The number of milliseconds that have passed
*/
int GameController::GetGameTicks()
{
#define kMILLISECONDS 1000
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + (tb.time & 0xfffff) * kMILLISECONDS;
	return (int)nCount / kTICK_PER_SECOND;
}