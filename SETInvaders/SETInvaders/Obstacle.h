/*
*	FILE		  : Obstacle.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the Obstacle class
*/

#pragma once
#include "BitmapObject.h"
#define kPLANET_FILE_STRING 500
#define kNUMBER_OF_PLANET_FILES 3

/**
 * \brief This class is used to represent the obstacles in the game. It very simply has 
 * the ability to set the location of an object and draw an object to the screen.
 */
class Obstacle : public BitmapObject
{
public:
	Obstacle(float x, float y, BitmapImage* image);
	Obstacle::Obstacle(BitmapImage* graphics);
	~Obstacle();
	//bool Draw(float gameW, float gameH, int gridXScale, int gridYScale, float scale);
};
