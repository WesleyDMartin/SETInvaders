/*
*	FILE		  : BitmapImage.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the BitmapImage class
*/

#pragma once

#include "Common.h"
#include <wincodec.h> //This is the WIC codec header - we need this to decode image files
#include "Graphics.h" //This includes both Windows and D2D libraries
#include <cstdlib>

#define kMAX_FILE_NAME 500
#define kINEXPLICABLE_DEFAULT_RECT_SIZE 10

#define kRED_INT_INDEX 0
#define kGREEN_INT_INDEX 1
#define kBLUE_INT_INDEX 2
#define kALPHA_INT_INDEX 3

#define kRED_THRESHOLD 150
#define kGREEN_THRESHOLD 140
#define kBLUE_THRESHOLD 150
#define kOPAQUE 1.0f

/**
 * \brief This class is used to draw a bitmap image to the screen, either
			full screen or in a specific location. It also contains the ability
			to apply a green chroma key effect to an object
 */
class BitmapImage
{
	Graphics* gfx; //Reference to the Graphics class
	ID2D1Bitmap* bmp; //This will hold our loaded and converted Bitmap file
	IWICImagingFactory* wicFactory;
	IWICBitmapDecoder* wicDecoder;
	IWICBitmapFrameDecode* wicFrame;
	IWICFormatConverter* wicConverter;
	IWICBitmapLock* pILock;
	IWICBitmap* pIBitmap;


public:
	//Constructor
	BitmapImage(char* filename, Graphics* gfx, bool doChroma);

	//Destructor
	~BitmapImage();

	//Draw bitmap to the render target
	void Draw(float topLeftX, float topLeftY, float w, float h);
	void FullScreenDraw();
	void GreenScreenFilter(BYTE* pv, int width, int height);
	bool DoChroma();
	Graphics* GetGraphics();
};
