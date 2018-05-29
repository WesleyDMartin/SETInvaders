/*
*	FILE		  : Level1.cpp
*   PROJECT		  :	GAS - Assignment 1
*   PROGRAMMER	  : Wes Martin
*	FIRST VERSION : 12/2/18
*	DESCRIPTION	  : This file contains the method declarations for the Level1 object
*/

// Huge shoutout to Russ for the starting point on this file
#include "GameController.h"
#include "Graphics.h"
#include "Level1.h"


int GameLevel::ticks = 0;

/**
 * \brief Constructor for Level1, calls the GameLevel object
 * \param obstacleScale The scale of the obstacles
 * \param enemyScale The scale of the enemy
 * \param enemySpeed The speed of the enemy
 * \param columns The number of columns
 * \param rows The number of rows
 * \param numberOfObstacles The number of obstacles
 * \param graphics The graphics driver to use
 * \param tileBackground Indicates if the background should be tiled or not
 */
Level1::Level1(float obstacleScale, float enemyScale, float enemySpeed, int columns, int rows,
               int numberOfObstacles, Graphics* graphics, bool tileBackground)
	: GameLevel(obstacleScale, enemyScale, enemySpeed, columns, rows, numberOfObstacles, graphics, tileBackground) {};



/**
 * \brief Load the initial values of the game
 */
void Level1::Load()
{
	// Calculate dimnesions of game area
	CalculateHeight();
	CalculateWidth();

	// Seed the generator
	srand((UINT)time(nullptr));

	// Initialize
	int x = kDEFAULT;
	int y = kDEFAULT;

	// Prepare the backdrop
	backDrop = new BitmapObject(kDEFAULT, kDEFAULT, new BitmapImage((char *)kBACKGROUND_FILE_NAME, this->gfx, false));
	backDrop->SetType(ObjectType::Background);
	sprites.push_back(backDrop);


	//// Setup the enemy
	enemy = new Enemy();


	// Set up the defender
	for (int i = 0; i < kNUMBER_OF_DEFENDERS; i++)
	{
		// The true as the third parameter implies chroma keying
		defender = new Defender(new BitmapImage(kDEFENDER_FILE_NAME, this->gfx, true));
		defender->SetTurretImage(new BitmapImage(kTURRET_FILE_NAME, this->gfx, true));
		sprites.push_back(defender);
	}

	// Prepare the obstacles
	char obstaclestring[kPLANET_FILE_STRING];
	for (int i = kDEFAULT; i < this->numberOfObstacles; i++)
	{
		// Create the filename
		sprintf(obstaclestring, kSPRITES_FILE_NAME, i % kNUMBER_OF_PLANET_FILES + kFIX_OFF_BY_ONE_ERROR);

		// Create the new planet
		obstacles[i] = new Obstacle(new BitmapImage(obstaclestring, this->gfx, true));
		sprites.push_back(obstacles[i]);
	}
	ResetLevel();
}



/**
 * \brief Reset the level to default values and scramble the locations of the obstacles
 */
void Level1::ResetLevel()
{
	// CLear the grid
	this->numberOfEnemies = kDEFAULT;
	this->numberOfDeadEnemies = kDEFAULT;
	gameGrid->clearGrid();
	int x = kDEFAULT;
	int y = kDEFAULT;

	// Flip through all the game objects and reset them
	for (int i = kDEFAULT; i < (int)sprites.size(); i++)
	{
		switch (sprites[i]->GetType())
		{
		case ObjectType::Unknown: 
			break;

		case ObjectType::Background: 
			break;

		case ObjectType::Enemy:
			// ENEMY
			// Pick a new column for the enemy
			((Enemy*)sprites[i])->~Enemy();
			sprites.erase(sprites.begin() + i);
			break;

		case ObjectType::Obstacle: 
			gameGrid->getEmptySlot(&x, &y, kHIGHEST_OBSTACLE_ROW);

			// Mark the slot as full
			gameGrid->fillSlot(x, y);

			// Update the location of the planet
			sprites[i]->SetPosition(
				gameGrid->XFromColumn(x, (int)renderWidth),
				gameGrid->YFromRow(y, (int)renderHeight)
			);
			break;

		case ObjectType::Defender:
			// DEFENDER
			// Pick a new column for the defender
			gameGrid->getEmptySlot(&x, &y, kHIGHEST_DEFENDER_ROW);

			((Defender*)sprites[i])->GetTurret()->SetPosition(
				gameGrid->XFromColumn((int)x, (int)renderWidth),
				gameGrid->YFromRow((int)y, (int)renderHeight)
			);

			// Update the location of the defender
			sprites[i]->SetPosition(
				gameGrid->XFromColumn((int)x, (int)renderWidth),
				gameGrid->YFromRow((int)y, (int)renderHeight)
			);

			gameGrid->fillSlot(x, y);
			break;

		default:;
		}
	}
}


/**
* \brief Calculate the height of the render target
*/
void Level1::CalculateHeight()
{
	renderHeight = (float)this->gfx->GetRenderTarget()->GetSize().height;
}



/**
 * \brief Calculate the width of the render target
 */
void Level1::CalculateWidth()
{
	renderWidth = (float)this->gfx->GetRenderTarget()->GetSize().width;
}



/**
 * \brief Get the graphics object used by the level
 * \return The graphics object of the level
 */
Graphics* Level1::GetGraphics()
{
	return gfx;
}



/**
 * \brief Unload all the game objects
 */
void Level1::Unload()
{
	backDrop->~BitmapObject();
	for (int i = kDEFAULT; i < this->numberOfObstacles; i++)
	{
		obstacles[i]->~Obstacle();
	}
}


/**
 * \brief Update the values of the object in the game
 */
void Level1::Update(int ticks)
{
	// Set number of elapsed ticks
	this->ticks = ticks;

	// If the correct number of ticks has passed, spawn new enemy
	if(ticks % kENEMY_SPAWN_RATE == kDEFAULT && this->numberOfEnemies < kNUMBER_OF_ENEMIES)
	{
		// Increase number of enemies
		this->numberOfEnemies++;
		
		// Create new enemy and set x/y speeds
		enemy = new Enemy();
		enemy->SetYSpeed((float)this->renderHeight / (float)this->rows / (float)kENEMY_SPEED_SCALE);
		enemy->SetXSpeed((float)this->renderWidth / (float)this->columns / (float)kENEMY_SPEED_SCALE);

		// Setup the enemy images
		char enemyString[kPLANET_FILE_STRING];
		for (int i = kDEFAULT; i < kNUMBER_OF_ENEMY_FILES; i++)
		{
			sprintf(enemyString, kENEMY_FILE_NAME, i % kNUMBER_OF_ENEMY_FILES + kFIX_OFF_BY_ONE_ERROR);
			enemy->AddImage(new BitmapImage(enemyString, this->gfx, true));
		}
		enemy->SetPosition(kDEFAULT + kFIX_OFF_BY_ONE_ERROR, kDEFAULT);

		// Add the enemy to the list of sprites
		sprites.push_back(enemy);
	}

	// Step through all the game objects and update them
	for (int i = kDEFAULT; i < (int)sprites.size(); i++)
	{
		switch(sprites[i]->GetType())
		{
		case ObjectType::Unknown:
			break;

		case ObjectType::Background:
			break;

		case ObjectType::Enemy: 

			// Update the image if needed, and move the ship
			((Enemy*)sprites[i])->ChangeImage((this->ticks / (int)kENEMY_SPEED_SCALE) % kNUMBER_OF_ENEMY_FILES);
			((Enemy*)sprites[i])->Move(gameGrid, this->renderWidth, this->renderHeight);

			// Check to see if enemy is off the bottom of the screen
			if (sprites[i]->GetY() >= this->renderHeight - 10) // Wanted a small threshold to make sure it gets triggered
			{
				// Erase and remove the enemy
				((Enemy*)sprites[i])->~Enemy();
				sprites.erase(sprites.begin() + i);
				this->numberOfDeadEnemies++;

				// If all enemies are gone, reset
				if(this->numberOfDeadEnemies == kNUMBER_OF_ENEMIES)
				{
					ResetLevel();
				}
			}

			// If collision detection is enabled, do this
			if (kCOLLISION_DETECTION_ENABLED &&
				gameGrid->isOccupied(gameGrid->ColumnFromX((int)sprites[i]->GetX(), (int)this->renderWidth),
					gameGrid->RowFromY((int)sprites[i]->GetY(), (int)this->renderHeight), this->renderWidth, this->renderHeight))
			{
				ResetLevel();
			}
			break;

		case ObjectType::Obstacle:
			break;

		case ObjectType::Defender: 
			{
				// Set the midpoint and then retaret the enemy
				sprites[i]->SetMidpoint((int)this->renderWidth / (int)this->columns, (int)this->renderHeight / (int)this->rows);
				((Defender*)sprites[i])->ReTarget
				(
					(Enemy*)sprites[((Defender*)sprites[i])->GetNearestEnemy(sprites)],
					this->renderHeight / gameGrid->getRows() * kENEMY_SIGHT
				);
			}
			break;

		default: ;
		}

	}
}



/**
 * \brief Based on the updated values of all the objects in the game, redraws the screen
 */
void Level1::Render()
{
	// Begin the draw
	this->gfx->BeginDraw();

	// Recalculate dimensions
	CalculateHeight();
	CalculateWidth();

	// Clear the screen
	this->gfx->ClearScreen(kMIN_COLOUR_VALUE, kMIN_COLOUR_VALUE, kMIN_COLOUR_VALUE);

	// Step through all the game objects and render them
	for (int i = kDEFAULT; i < (int)sprites.size(); i++)
	{
		switch(sprites[i]->GetType())
		{
		case ObjectType::Background: 
			// Render the backdrops
			if (this->tileBackground)
			{
				for (int i = 0; i < this->columns; i++)
				{
					backDrop->SetPosition(i * this->renderWidth / this->columns, kDEFAULT);
					backDrop->Draw(this->renderWidth / this->columns, this->renderHeight);
				}
			}
			else
			{
				backDrop->SetPosition(kDEFAULT, kDEFAULT);
				backDrop->Draw(this->renderWidth, this->renderHeight);
			}
			break;

		case ObjectType::Unknown: 
		case ObjectType::Enemy: 
			sprites[i]->Draw(this->renderWidth, this->renderHeight, this->columns, this->rows, this->enemyScale);
			break;

		case ObjectType::Obstacle: 
			sprites[i]->Draw(this->renderWidth, this->renderHeight, this->columns, this->rows, this->obstacleScale);
			break;

		case ObjectType::Defender:
			sprites[i]->Draw(this->renderWidth, this->renderHeight, this->columns, this->rows, kDEFENDER_SCALE);
			((Defender*)sprites[i])->GetTurret()->Draw(this->renderWidth, this->renderHeight, this->columns, this->rows, kTURRET_SCALE);
			break;

		default:
			sprites[i]->Draw(this->renderWidth, this->renderHeight, this->columns, this->rows, 1);
		}
	}
	// All done 
	this->gfx->EndDraw();
}
