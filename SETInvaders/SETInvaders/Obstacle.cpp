/*
*	FILE		  : .cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the
*/

#include "Obstacle.h"


/**
 * \brief 
 * \param x The top left x corner of the obstacle
 * \param y The top left y corner of the obstacle
 * \param image The image of the obstacle to be used
 */
Obstacle::Obstacle(float x, float y, BitmapImage* image) : BitmapObject(x, y, image) 
{
	SetType(ObjectType::Obstacle);
};

/**
* \brief Constructs an enemy with no preset values, except graphics driver
* \param graphics The graphics driver to create the enemy
*/
Obstacle::Obstacle(BitmapImage* graphics)
{
	SetType(ObjectType::Obstacle);
	this->SetImage(graphics);
	SetPosition(kDEFAULT, kDEFAULT);
}

/**
 * \brief Destructor for the obstacle
 */
Obstacle::~Obstacle() = default;
