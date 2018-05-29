/*
*	FILE		  : main.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the main entry point for SETInvaders
*/

// Huge shoutout to Russ for the starting point on this file
#include <Windows.h>
#include "Common.h"
#include "Graphics.h"
#include "Level1.h"
#include "GameController.h"
#include <thread>
Graphics* graphics;
bool setToRun;
int getMilliCount();


/**
* \brief The message handler for the program
*/
LONG_PTR CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(kDEFAULT);
		return kSUCCESS;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


/**
 * \brief This is the main entry point for the game, it is called by the OS
 * \return The status of the program on completion
 */
int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow
)
{
	//Create the window class
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW;

	// Register the window class
	RegisterClassEx(&windowclass);


	RECT rect = {kDEFAULT, kDEFAULT, kWINDOW_WIDTH, kWINDOW_HEIGHT}; // Set the size of the window
	AdjustWindowRectEx(&rect, WS_OVERLAPPED, false, WS_EX_OVERLAPPEDWINDOW); // Set the window to the rectangle size

	// Creates a windows handle and connects it to the window class created above. The rect is used to set the
	// size of the window being created
	HWND windowhandle = CreateWindowEx
	(WS_EX_OVERLAPPEDWINDOW,
	 "MainWindow",
	 "SETInvaders",
	 WS_OVERLAPPEDWINDOW,
	 kSTARTING_X,
	 kSTARTING_Y,
	 rect.right - rect.left,
	 rect.bottom - rect.top,
	 nullptr,
	 nullptr,
	 hInstance,
	 nullptr);

	// Make sure the window was created sucessfully
	if (!windowhandle)
	{
		return kFAILURE;
	}

	// Setup the graphics object
	graphics = new Graphics();
	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return kFAILURE;
	}

	// Show the window
	ShowWindow(windowhandle, nCmdShow);

	// Instantaite the new level
	Level1* level = new Level1(
		(float)kROADBLOCK_SCALE, 
		(float)kENEMY_SCALE, 
		kENEMY_SPEED, 
		kGAME_GRID_WIDTH,            
		kGAME_GRID_HEIGHT,
		kNUMBER_OF_OBSTACLES, 
		graphics, 
		kTILE_BACKGROUND);

	GameController::LoadInitialLevel(level);

	// Message to recieve incoming messages to the program
	MSG message;
	message.message = WM_NULL;
	setToRun = true;

#pragma region GameLoop
	// This is the game loop that will power the game. It will run endlessly
	while (message.message != WM_QUIT)
	{
		// If a message exists, call WINPROC, otherwise, continue with the game
		if (PeekMessage(&message, nullptr, kDEFAULT, kDEFAULT, PM_REMOVE))
		{
			DispatchMessage(&message);
		}
		else
		{
			// Check the current status of the game
			GameController::Update();

			// Redraw everything
			GameController::Render();
		}
	}

#pragma endregion
	return kSUCCESS;
}



