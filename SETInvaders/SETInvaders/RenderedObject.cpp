/*
*	FILE		  : RenderedObject.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the method declarations for the RenderedObject class
*/

#include "RenderedObject.h"

/**
* \brief Constructs a renderable object with no preset values
*/
RenderedObject::RenderedObject() : GameObject()
{
	graphics = nullptr;
	SetX(kDEFAULT);
	SetY(kDEFAULT);
	a = kMAX_COLOUR_VALUE;
	r = kDEFAULT;
	g = kDEFAULT;
	b = kDEFAULT;
	w = kDEFAULT;
	h = kDEFAULT;
}


/**
* \brief Constructs a renderable object with no preset values, except graphics driver
* \param graphic The graphics driver to create the object
*/
RenderedObject::RenderedObject(Graphics* graphic) : GameObject()
{
	graphics = graphic;
	SetX(kDEFAULT);
	SetY(kDEFAULT);
	a = kMAX_COLOUR_VALUE;
	r = kDEFAULT;
	g = kDEFAULT;
	b = kDEFAULT;
	w = kDEFAULT;
	h = kDEFAULT;
}



/**
 * \brief Constructs a renderable object with set location
 * \param x The x value of top left corner
 * \param y The y value of top left corner
 * \param graphic The graphics driver to create the object
 */
RenderedObject::RenderedObject(float x, float y, Graphics* graphic) : GameObject()
{
	graphics = graphic;
	SetX(x);
	SetY(y);
	a = kMAX_COLOUR_VALUE;
	r = kDEFAULT;
	g = kDEFAULT;
	b = kDEFAULT;
	w = kDEFAULT;
	h = kDEFAULT;
}



/**
 * \brief Constructs a renderable object with set size and location
 * \param x The x value of top left corner
 * \param y The y value of top left corner
 * \param w The width of the object
 * \param h The height of the object
 * \param graphic The graphics driver to create the object
 */
RenderedObject::RenderedObject(float x, float y, float w, float h, Graphics* graphic) : GameObject()
{
	graphics = graphic;
	SetX(x);
	SetY(y);
	a = kMAX_COLOUR_VALUE;
	r = kDEFAULT;
	g = kDEFAULT;
	b = kDEFAULT;
	this->w = w;
	this->h = h;
}



/**
 * \brief Sets the color of the object
 * \param r The red color component
 * \param g The green color component
 * \param b The blue color component
 * \param a The alpha color component
 * \return Status indicating success of set
 */
bool RenderedObject::SetColor(float r, float g, float b, float a)
{
	bool ret = true;
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	return ret;
}



/**
 * \brief Gets the graphics object being used
 * \return The graphics object being used
 */
Graphics* RenderedObject::GetGraphics()
{
	return graphics;
}



/**
 * \brief 
 * \param graphics The new graphics object
 * \return Status indicating success of set
 */
bool RenderedObject::SetGraphics(Graphics* graphics)
{
	bool ret = true;
	this->graphics = graphics;
	return ret;
}



/**
 * \brief Sets the size of the object
 * \param w The new width
 * \param h The new height
 * \return Status indicating success of set
 */
bool RenderedObject::SetSize(float w, float h)
{
	bool ret = true;
	this->w = w;
	this->h = h;
	return ret;
}



/**
* \brief Gets the value of the red color component
* \return The value of the red color component
*/
float RenderedObject::GetR()
{
	return r;
}



/**
* \brief Gets the value of the green color component
* \return The value of the green color component
*/
float RenderedObject::GetG()
{
	return g;
}



/**
* \brief Gets the value of the blue color component
* \return The value of the blue color component
*/
float RenderedObject::GetB()
{
	return b;
}



/**
* \brief Gets the value of the alpha color component
* \return The value of the alpha color component
*/
float RenderedObject::GetA()
{
	return a;
}



/**
* \brief Gets the width of the object
* \return The width of the object
*/
float RenderedObject::GetW()
{
	return w;
}



/**
 * \brief Gets the height of the object
 * \return The height of the object
 */
float RenderedObject::GetH()
{
	return h;
}
