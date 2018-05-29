/*
*	FILE		  : Enemy.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the method declarations for the Enemy class
*/

#include "Enemy.h"

/**
* \brief Constructs an enemy with all default
*/
Enemy::Enemy()
{
	SetType(ObjectType::Enemy);
	SetPosition(kDEFAULT, kDEFAULT);
}


/**
* \brief Constructs an enemy with no preset values, except graphics driver
* \param graphics The graphics driver to create the enemy
*/
Enemy::Enemy(BitmapImage* graphics)
{
	SetType(ObjectType::Enemy);
	this->SetImage(graphics);
	SetPosition(kDEFAULT, kDEFAULT);
}

/**
* \brief Constructs an enemy with no preset values, except graphics driver
* \param graphics The graphics driver to create the enemy
*/
Enemy::Enemy(std::vector<BitmapImage*> graphics)
{
	SetType(ObjectType::Enemy);
	this->images = graphics;
	SetPosition(kDEFAULT, kDEFAULT);
}


/**
 * \brief Cosntrutor for an enemy with all values set
 * \param x The x value of top left corner
 * \param y The y value of top left corner
 * \param w The width of the object
 * \param h The height of the object
 * \param r The red color component
 * \param g The green color component
 * \param b The blue color component
 * \param a The alpha color component
 * \param graphics The graphics driver to create the enemy
 */
Enemy::Enemy(float x, float y, BitmapImage* graphics)
{
	SetType(ObjectType::Enemy);
	this->SetImage(graphics);
	SetPosition(x, y);
}



/**
 * \brief Used to set the graphics image array and the location of the image
 * \param x The x value of top left corner
 * \param y The y value of top left corner
 * \param graphics The graphics driver to create the enemy
 */
Enemy::Enemy(float x, float y, std::vector<BitmapImage*> graphics)
{
}


/**
* \brief Destructor for the enemy
*/
Enemy::~Enemy()
{
}


/**
* \brief
* \param xSpeed Sets the vertical speed of the enemy
* \return Success of the value set
*/
bool Enemy::SetXSpeed(float xSpeed)
{
	bool ret = true;
	this->xSpeed = xSpeed;
	return ret;
}


/**
* \brief Gets the horizontal speed of the enemy
* \return The speed of the enemy
*/
float Enemy::GetXSpeed()
{
	return xSpeed;
}



/**
 * \brief
 * \param ySpeed Sets the horizontal speed of the enemy
 * \return Success of the value set
 */
bool Enemy::SetYSpeed(float ySpeed)
{
	bool ret = true;
	this->ySpeed = ySpeed;
	return ret;
}



/**
 * \brief Gets the vertical speed of the enemy
 * \return The speed of the enemy
 */
float Enemy::GetYSpeed()
{
	return ySpeed;
}

bool Enemy::AddImage(BitmapImage* image)
{
	bool ret = true;
	images.push_back(image);
	return ret;
}

std::vector<BitmapImage*> Enemy::GetImages()
{
	return images;
}




/**
 * \brief Used to calculate the movement of the enemy spaceship, based off the grid and dimensions of the game
 * \param grid The grid of the game
 * \param gameWidth The width of the game area
 * \param gameHeight The height of the game area
 * \return Success or failure of the movement
 */
bool Enemy::Move(LevelGrid* grid, float gameWidth, float gameHeight)
{
	int currentRow = kDEFAULT;
	bool ret = true;

	// Check to see if spaceship is at either edge of screen
	if (this->GetX() <= kLEFT_EDGE || grid->ColumnFromX((int)this->GetX(), (int)gameWidth) == grid->getRows() - kFIX_OFF_BY_ONE_ERROR)
	{
		// Move ship vertically
		currentRow = grid->RowFromY((int)this->GetY(), (int)gameHeight);
		this->SetY(this->GetY() + this->GetYSpeed());

		// Check to see if spaceship has fully moved down to the next row
		if(grid->RowFromY((int)this->GetY(), (int)gameHeight) != currentRow)
		{
			this->SetXSpeed(this->GetXSpeed() * kINVERTED);
			this->SetX(this->GetX() + this->GetXSpeed());
		}
	}
	else
	{
		// Otherwise, move horizontally
		this->SetX(this->GetX() + this->GetXSpeed());
	}


	return ret;

	//----------------REVISIT ONCE YOU LEARN HOW IT WORKS-----------------------
	//D2D1::Matrix3x2F T;
	//T = D2D1::Matrix3x2F::Translation(0,0);
	//this->SetTranslation(T);
}



/**
 * \brief Used to change the image of the spaceship
 * \param imageIndex 
 * \return Indicates success of image change
 */
bool Enemy::ChangeImage(int imageIndex)
{
	bool ret = true;
	if(imageIndex < images.size())
	{
		this->SetImage(images[imageIndex]);
	}
	else
	{
		ret = false;
	}

	return ret;
}
