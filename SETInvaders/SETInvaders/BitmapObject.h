/*
*	FILE		  : BitmapObject.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the BitmapObject class
*/

#pragma once
#include "GameObject.h"

/**
 * \brief This class represents a bitmap object. It has basic location values
 *		and the ability to draw the image to the screen at the location
 */
class BitmapObject : public GameObject
{
	BitmapImage* image;

public:
	BitmapObject();
	BitmapObject(float x, float y, BitmapImage* image);
	~BitmapObject();
	bool Draw(float gameW, float gameH, int gridXScale, int gridYScale, float scale);
	bool Draw(float w, float h);
	bool SetImage(BitmapImage* image);
	BitmapImage* GetImage();
};
