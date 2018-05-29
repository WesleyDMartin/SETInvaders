/*
*	FILE		  : Graphics.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the method declarations for the Graphics class, 
*				  : This file is only possible because of Russ, so thanks
*/

#include "Graphics.h"

/***********************************************************************************
The intent of the Graphics class is to handle our DirectX calls, and to be largely responsible 
for managing the rendertarget.

-Russ Foubert
******************************************************************************************/


/**
* \brief Destructor for Graphics class
*/
Graphics::Graphics()
{
	factory = nullptr;
	rendertarget = nullptr;
	brush = nullptr;
}



/**
 * \brief Destructor for Graphics class
 */
Graphics::~Graphics()
{
	if (factory) factory->Release();
	if (rendertarget) rendertarget->Release();
	if (brush) brush->Release();
}



/**
 * \brief Creates the rendeer target that will be used to draw the objects
 * \param windowHandle The handle to the window which the graphics object will draw to
 * \return The success of the initialization of the Graphics object
 */
bool Graphics::Init(HWND windowHandle)
{
	// Create the 'create' factor
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (hr != S_OK) return false;

	// Get the information about the main window
	RECT rect;
	GetClientRect(windowHandle, &rect); //set the rect's right and bottom properties = the client window's size
	hr = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&rendertarget);
	if (hr != S_OK) return false;

	// Create the drawing brush
	hr = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (hr != S_OK) return false;
	return true;
}



/**
 * \brief Sets the color of the triangle
 * \param r The red value of the triangle
 * \param g The green value of the triangle
 * \param b The blue value of the triangle
 */
void Graphics::ClearScreen(float r, float g, float b)
{
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}


/**
 * \brief Draws a triangle on the screen using the set values
 * \param x The X coordinate of the triangle
 * \param y The Y coordinate of the triangle
 * \param h The height of the triangle
 * \param w The width of the triangle
 * \param r The red value of the triangle
 * \param g The green value of the triangle
 * \param b The blue value of the triangle
 * \param a The alpha value of the triangle
 */
void Graphics::DrawTriangle(float x, float y, float h, float w, float r, float g, float b, float a)
{
#define kNUMBER_OF_POINTS_IN_TRAINGLE 3
	HRESULT hr;
	ID2D1PathGeometry* pathGeometry = nullptr;
	hr = factory->CreatePathGeometry(&pathGeometry);
	if (SUCCEEDED(hr))
	{
		// Prepare object to construct triangle
		ID2D1GeometrySink* pSink = nullptr;
		hr = pathGeometry->Open(&pSink);
		if (SUCCEEDED(hr))
		{
			pSink->SetFillMode(D2D1_FILL_MODE_WINDING);
			pSink->BeginFigure(
				D2D1::Point2F(x, y),
				D2D1_FIGURE_BEGIN_FILLED
			);

			// Set the points for the triangle
			D2D1_POINT_2F points[kNUMBER_OF_POINTS_IN_TRAINGLE] = {
				D2D1::Point2F(x + w / kCUT_IN_HALF, y - h),
				D2D1::Point2F(x - w / kCUT_IN_HALF, y - h),
				D2D1::Point2F(x, y)
			};

			// Construct the triangle
			pSink->AddLines(points, ARRAYSIZE(points));
			pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
			pSink->Close();
			brush->SetColor(D2D1::ColorF(r, g, b, a));

			// Draw the triangle
			rendertarget->DrawGeometry(pathGeometry, brush);
			rendertarget->FillGeometry(pathGeometry, brush);
		}
	}
}
