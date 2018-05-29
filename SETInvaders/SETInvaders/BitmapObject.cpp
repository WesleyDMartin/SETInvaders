/*
*	FILE		  : BitmapObject.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the method declarations for the BitmapObject class.
*/

#include "BitmapObject.h"



/**
 * \brief The basic constructor, does nothing
 */
BitmapObject::BitmapObject() : GameObject()
{
	SetX(0);
	SetY(0);
	SetRotation(D2D1::Matrix3x2F::Identity());
	SetTranslation(D2D1::Matrix3x2F::Identity());

	image = nullptr;
}



/**
 * \brief Standard construtor for an image. Instantiantes an image object with location and image
 * \param x The X coordinates of image
 * \param y The Y coordinates of image
 * \param image The instantiated image to be used
 */
BitmapObject::BitmapObject(float x, float y, BitmapImage* image) : GameObject()
{
	SetX(x);
	SetY(y);
	this->image = image;
}



/**
 * \brief Destructor for the bitmap object
 */
BitmapObject::~BitmapObject()
{
	delete image;
}



/**
 * \brief Sets the BitmapImage file being used
 * \param image BitmapImage file to be used
 * \return Success of bitmap update
 */
bool BitmapObject::SetImage(BitmapImage* image)
{
	this->image = image;
	return false;
}



/**
 * \brief Returns the BitmapImage file being used
 * \return The bitmap image being used
 */
BitmapImage* BitmapObject::GetImage()
{
	return image;
}



/**
 * \brief Draws the bitmap to the screen at a specific location
 * \param w Width of bitmap
 * \param h Height of bitmap
 * \return Success of bitmap draw
 */
bool BitmapObject::Draw(float w, float h)
{
	bool ret = true;
	GetImage()->Draw(
		GetX(),
		GetY(),
		w,
		h);
	return ret;
}


/**
* \brief Draws the bitmap to the screen at a specific location
* \param w Width of bitmap
* \param h Height of bitmap
* \return Success of bitmap draw
*/
bool BitmapObject::Draw(float gameW, float gameH, int gridXScale, int gridYScale, float scale)
{
	image->GetGraphics()->GetRenderTarget()->SetTransform(this->GetRotation());
	bool ret = true;
	GetImage()->Draw(
		GetX() + (gameW / (gridXScale * kCUT_IN_HALF)) - (scale * gameW / (gridXScale * kCUT_IN_HALF)),
		GetY() + (gameH / (gridYScale * kCUT_IN_HALF)) - (scale * gameH / (gridYScale * kCUT_IN_HALF)),
		(float)(scale * gameW / gridXScale),
		(float)(scale * gameH / gridYScale));

	image->GetGraphics()->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	return ret;
}