/*
*	FILE		  : GameObject.h
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the definition of the GameObject class
*/

#include "BitmapImage.h"
#include "DirectXMath.h"
#include "D2d1_1.h"

enum class ObjectType
{
	Unknown = 0,
	Background,
	Enemy,
	Obstacle,
	Defender,
	Turret
};

#pragma once
/**
 * \brief This is the root of all game objects. It has the very simple ability to
 * update and retrieve the location of an object. It has no drawing or rendering ability.
 */
class GameObject
{
	static int uid;
	float x;
	float y;
	int id;
	ObjectType type;
	D2D1::Matrix3x2F rotation;
	D2D1::Matrix3x2F translation;
	D2D1_POINT_2F midpoint;


public:
	GameObject();
	GameObject(ObjectType type);
	virtual ~GameObject() = default;
	virtual bool Draw(float, float, int, int, float) = kMAKE_VIRTUAL;
	bool SetPosition(float x, float y);
	int GetID();
	float GetX();
	bool SetX(float xPosition);
	float GetY();
	bool SetY(float yPosition);
	bool SetMidpoint(int columnWidth, int rowHeight);
	D2D1_POINT_2F GetMidpoint();
	ObjectType GetType();
	bool SetType(ObjectType type);
	bool SetRotation(D2D1::Matrix3x2F rotation);
	D2D1::Matrix3x2F GetRotation();
	bool SetTranslation(D2D1::Matrix3x2F translation);
	D2D1::Matrix3x2F GetTranslation();
};
