/*
*	FILE		  : RenderedObject.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the RenderedObject class
*/

#pragma once
#include "GameObject.h"

/**
 * \brief This class represents the RenderedObject class which is the foundation
 * of any object that needs to be rendered.
 */
class RenderedObject : public GameObject
{
	Graphics* graphics;
	float a;
	float r;
	float g;
	float b;
	float w;
	float h;

public:

	RenderedObject();
	RenderedObject(Graphics* graphic);
	RenderedObject(float x, float y, Graphics* graphic);
	RenderedObject(float x, float y, float w, float h, Graphics* graphic);
	bool SetColor(float r, float g, float b, float a);
	Graphics* GetGraphics();
	bool SetGraphics(Graphics* graphics);
	bool SetSize(float w, float h);
	virtual bool RenderObject(float gameW, float gameH, int gridXScale, int gridYScale, float scale) = kMAKE_VIRTUAL;
	float GetR();
	float GetG();
	float GetB();
	float GetA();
	float GetW();
	float GetH();
};
