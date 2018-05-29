/*
*	FILE		  : GameObject.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the GameObject definition
*/

#include "GameObject.h"

/**
 * \brief Used to globally identify all game objects
 */
int GameObject::uid = 0;

/**
 * \brief Default constructor, sets ID
 */
GameObject::GameObject()
{
	this->type = ObjectType::Unknown;
	id = uid++;
}


GameObject::GameObject(ObjectType type)
{
	this->type = type;
	id = uid++;
}

/**
 * \brief The new position for the game object
 * \param x The X location for the game object
 * \param y The Y location for the game object
 * \return Success status of setting the location
 */
bool GameObject::SetPosition(float x, float y)
{
	bool ret = true;
	ret = SetY(y);
	ret = SetX(x);
	return ret;
}


/**
* \brief Gets the X value for the game object
* \return Success status of setting the value
*/
float GameObject::GetX()
{
	return x;
}

/**
* \brief Gets the X value for the game object
* \return Success status of setting the value
*/
int GameObject::GetID()
{
	return id;
}



/**
* \brief Sets the X value for the game object
* \param xPosition The X value for the game object
* \return Success status of setting the value
*/
bool GameObject::SetX(float xPosition)
{
	bool ret = true;
	x = xPosition;
	return ret;
}



/**
* \brief Gets the Y value for the game object
* \return Success status of setting the value
*/
float GameObject::GetY()
{
	return y;
}



/**
 * \brief Sets the Y value for the game object
 * \param yPosition The Y value for the game object
 * \return Success status of setting the value
 */
bool GameObject::SetY(float yPosition)
{
	bool ret = true;
	y = yPosition;
	return ret;
}



/**
 * \brief Calculates and sets the midpoint of the object
 * \param columnWidth The width of the object
 * \param rowHeight The height of the object
 * \return Success of the set
 */
bool GameObject::SetMidpoint(int columnWidth, int rowHeight)
{
	bool ret = true;
	midpoint = D2D1::Point2F(GetX() + columnWidth/kCUT_IN_HALF, GetY() + rowHeight / kCUT_IN_HALF);
	return ret;
}


/**
* \brief Gets the midpoint of the object
* \return The midpoint
*/
D2D1_POINT_2F GameObject::GetMidpoint()
{
	return midpoint;
}


/**
* \brief Gets the type of the object
* \return The type
*/
 ObjectType GameObject::GetType()
 {
	 return this->type;
 }


 /**
 * \brief Sets the type of the object
 * \param type The type to be set
 * \return Success or failure of set
 */
 bool GameObject::SetType(ObjectType type)
 {
	 bool ret = true;
	 this->type = type;
	 return ret;
 }


 /**
 * \brief Sets the rotation matrix of the object
 * \param rotation The rotation matrix to be set
 * \return Success or failure of set
 */
bool GameObject::SetRotation(D2D1::Matrix3x2F rotation)
{
	bool ret = true;
	this->rotation = rotation;
	return ret;
}

/**
* \brief Gets the rotation matrix of the object
* \return The rotation matrix
*/
D2D1::Matrix3x2F GameObject::GetRotation()
{
	return rotation;
}



/**
 * \brief Sets the translation matrix of the object
 * \param translation The translation matrix to be set
 * \return Success or failure of set
 */
bool GameObject::SetTranslation(D2D1::Matrix3x2F translation)
{
	bool ret = true;
	this->translation = translation;
	return ret;
}



/**
 * \brief Gets the translation matrix of the object
 * \return The translation matrix
 */
D2D1::Matrix3x2F GameObject::GetTranslation()
{
	return translation;
}
