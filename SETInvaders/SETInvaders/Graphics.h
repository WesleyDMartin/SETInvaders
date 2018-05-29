/*
*	FILE		  : Graphics.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the Graphics class
*/

#pragma once
#include <Windows.h>
#include <d2d1.h>
#include "Common.h"

/**
 * \brief The graphics object is used to draw objects to the screen. It can 
 * be used to either drawn a renderable object (Currently triangle is the only
 * viable option) or assist in drawing a bitmap image
 */
class Graphics
{
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* rendertarget;
	ID2D1SolidColorBrush* brush;

public:
	Graphics();
	~Graphics();
	bool Init(HWND windowHandle);
	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }
	void ClearScreen(float r, float g, float b);
	void Graphics::DrawTriangle(float x, float y, float h, float w, float r, float g, float b, float a);
	ID2D1RenderTarget* GetRenderTarget()
	{
		return rendertarget;
	}
};
