/*
*	FILE		  : Defender.h
*   PROJECT		  :	GAS - Assignment 2
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 20/3/18
*	DESCRIPTION	  : This file contains the definition of the Defender class
*/

#pragma once
#include "BitmapObject.h"
#include "LevelGrid.h"
#define kNUMBER_OF_DEFENDER_FILES 1

/**
 * \brief This class represents the defender class which is a combination of the defender
 * base and the defender turret images.
 */
class Defender :
	public BitmapObject
{
	BitmapObject* turret{};
public:
	Defender();
	Defender(BitmapImage* image);
	Defender(float x, float y, BitmapImage* image);
	bool SetTurretImage(BitmapImage *turret);
	BitmapObject* GetTurret();
	~Defender();
	void ReTarget(GameObject* enemy, float rowHeight);
	float CalculateDistanceToEnemy(GameObject* enemy);
	int GetNearestEnemy(std::vector<GameObject*> sprites);
};

