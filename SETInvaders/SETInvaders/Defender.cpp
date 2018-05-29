/*
*	FILE		  : Defender.cpp
*   PROJECT		  :	GAS - Assignment 2
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 20/3/18
*	DESCRIPTION	  : This file contains the method declarations for the Defender class
*/

#include "Defender.h"



/**
 * \brief The default constructor for a defender object, sets the object type
 */
Defender::Defender()
{
	SetType(ObjectType::Defender);
}



/**
 * \brief The basic constructor for a defender object, sets the image and object type
 * \param image The image for the defender image
 */
Defender::Defender(BitmapImage* image)
{
	SetType(ObjectType::Defender);
	this->SetImage(image);
}



/**
 * \brief The standard constructor for the defender object, ssets the x and y location,
 * the defender image, and the type
 * 
 * \param x Horizontal location of the defender
 * \param y Vertical location of the defender
 * \param image The image for the defender image
 */
Defender::Defender(float x, float y, BitmapImage* image)
{
	SetType(ObjectType::Defender);
	this->SetImage(image);
	this->SetX(x);
	this->SetY(y);
}


/**
 * \brief Default constructor for defender
 */
Defender::~Defender(){}


/**
* \brief Set the image file for the turret
* \param turret The image to be used as the turret image
* \return Indicates success of setting turret image
*/
bool Defender::SetTurretImage(BitmapImage *turret)
{
	bool ret = true;
	this->turret = new BitmapObject(this->GetX(), this->GetY(), turret);
	return ret;
}



/**
* \brief Get the image of the turret
* \return The turret image
*/
BitmapObject* Defender::GetTurret()
{
	return turret;
}



/**
 * \brief Used to realign the defenders turret to point at the enemy object
 * provided in the parameter list. It can only point at enemies that are lower than 
 * the enemyRow provided
 * 
 * \param enemy The enemy that the defender should aim at
 * \param enemyRow The minimum row that the defender can target at
 * \param sight How far the turret can see
 */
void Defender::ReTarget(GameObject* enemy, float sight)
{
	// Only do anything if the enemy is across the target row
	if (CalculateDistanceToEnemy(enemy) <= sight)
	{
		// Get the vector to the target and the source
		DirectX::XMVECTOR target = DirectX::XMVectorSet(enemy->GetX() - GetX(), enemy->GetY() - GetY(), kDEFAULT, kDEFAULT);
		DirectX::XMVECTOR source = DirectX::XMVectorSet(kDEFAULT, kINVERTED, kDEFAULT, kDEFAULT);


		// Prepare normalized vectors
		DirectX::XMVECTOR target_n = DirectX::XMVector2Normalize(target);
		DirectX::XMVECTOR source_n = DirectX::XMVector2Normalize(source);

		// Check angle
		float targetAngle = DirectX::XMConvertToDegrees(DirectX::XMVectorGetY((DirectX::XMVectorACos(DirectX::XMVector2Dot(target_n, source_n)))));
		if (enemy->GetX() <= GetX())
		{
			targetAngle *= kINVERTED;
		}



		// Calculate the rotation matrix
		D2D1::Matrix3x2F R;
		if (enemy->GetType() == ObjectType::Enemy)
		{
			R = D2D1::Matrix3x2F::Rotation(targetAngle, GetMidpoint());
		}

		// Apply the rotation
		turret->SetRotation(R);
	}
	else
	{
		// Apply the default identity matrix
		turret->SetRotation(D2D1::Matrix3x2F::Identity());
	}
}



/**
* \brief Used to calculate the distance between the defender and the give
* enemy spaceship
*
* \param enemy The enemy that the defender is targeting
*/
float Defender::CalculateDistanceToEnemy(GameObject* enemy)
{
	DirectX::XMVECTOR target = DirectX::XMVectorSet(enemy->GetX() - GetX(), enemy->GetY() - GetY(), kDEFAULT, kDEFAULT);
	DirectX::XMVECTOR length = DirectX::XMVector2Length(target);

	float distance = kDEFAULT;
	DirectX::XMStoreFloat(&distance, length);
	return distance;
}


/**
* \brief Used to calculate the distance between the defender and the give
* enemy spaceship
*
* \param enemy The enemy that the defender is targeting
*/
int Defender::GetNearestEnemy(std::vector<GameObject*> sprites)
{
	float closestEnemy = INT_MAX;
	int closestEnemyIndex = 0;

	// Cycle throuh all sprites
	for (int i = kDEFAULT; i < sprites.size(); i++)
	{
		if(sprites[i]->GetType() == ObjectType::Enemy && CalculateDistanceToEnemy(sprites[i]) < closestEnemy)
		{
			closestEnemy = CalculateDistanceToEnemy(sprites[i]);
			closestEnemyIndex = i;
		}
	}

	// Return the index of the closest one
	return closestEnemyIndex;
}


