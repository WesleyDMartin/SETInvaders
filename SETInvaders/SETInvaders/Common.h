/*
*	FILE		  : Common.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains standard values that are used to control
*				  : operations accross the program
*/

#pragma once

#include <stdio.h>
#include <vector>
#include <DirectXMath.h>
#pragma warning(disable: 4996)

#pragma region GameControls

#define kGAME_GRID_HEIGHT				10
#define kGAME_GRID_WIDTH				10
#define kROADBLOCK_SCALE				.5
#define kENEMY_SCALE					.65
#define kDEFENDER_SCALE					.65
#define kENEMY_SPEED					1
#define kTURRET_SCALE					kDEFENDER_SCALE * 2
#define kNUMBER_OF_OBSTACLES			3
#define kNUMBER_OF_DEFENDERS			6
#define kENEMY_SPAWN_RATE				25
#define kNUMBER_OF_ENEMIES				35
#define kHIGHEST_OBSTACLE_ROW			4
#define kHIGHEST_DEFENDER_ROW			8
#define kENEMY_SIGHT					4
#define kSPRITES_FILE_NAME				"Assets/Planet%d.bmp"
#define kBACKGROUND_FILE_NAME			"Assets/SectorBackground.bmp"
#define kENEMY_FILE_NAME				"Assets/A2En%d.png"
#define kDEFENDER_FILE_NAME				"Assets/DSAT2.bmp"
#define kTURRET_FILE_NAME				"Assets/Turret.bmp"
#define kCOLLISION_DETECTION_ENABLED	false
#define kTILE_BACKGROUND				false
#define kLEFT_EDGE						0
#define kINVERTED						-1
#define kSTOPPED						0
#define kENEMY_SPEED_SCALE				25.0

#pragma endregion


#define kWINDOW_HEIGHT 768
#define kWINDOW_WIDTH 1024
#define kSTARTING_X 100
#define kSTARTING_Y 100

#define kTICK_PER_SECOND 20

#define kMAX_COLOUR_VALUE 255.0f
#define kMIN_COLOUR_VALUE 0.0f
#define kFIX_OFF_BY_ONE_ERROR 1
#define kCUT_IN_HALF 2
#define kSIZE_OF_INT 4

#define kBLOCK_IS_FULL 1
#define kBLOCK_IS_EMPTY 0

#define kSUCCESS 0
#define kFAILURE -1
#define kUNDEFINED -1
#define kDEFAULT 0
#define kTIME_SCALAR 4
#define kMAKE_VIRTUAL 0
