/*
  Program name:			Rougelike
  Project file name:	SpriteList.cpp
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				Will hold a linked list of enemny sprites
  Description:			This class will contain a linked list with the enemy sprites, the class will be able to add, delete, move, count etc..
  Known Bugs:			Nothing currently
*/

#include "SpriteList.h"

SpriteList::SpriteList()
{
	head = nullptr;
	tail = nullptr;
}

// add sprite to the linked list
void SpriteList::AddSprite(Sprite^ newSprite)
{
	if (tail == nullptr)
	{
		head = newSprite;
		tail = newSprite;
	}
	else
	{
		tail->Next = newSprite;
		tail = newSprite;
	}
}

// move each sprite in linked list 
void SpriteList::MoveSprites()
{
	Sprite^ spriteWalker = head;

	while (spriteWalker != nullptr)
	{
		spriteWalker->Move();
		spriteWalker = spriteWalker->Next;
	}
}

// draw each sprite in linked list
void SpriteList::DrawSprites()
{
	Sprite^ spriteWalker = head;

	while (spriteWalker != nullptr)
	{
		spriteWalker->Draw();
		spriteWalker = spriteWalker->Next;
	}
}

// update the sprites frame, cycle through the spritesheet
void SpriteList::UpdateFrame()
{
	Sprite^ spriteWalker = head;

	while (spriteWalker != nullptr)
	{
		spriteWalker->UpdateFrame();
		spriteWalker = spriteWalker->Next;
	}
}

// removed all the sprites from the linked list
void SpriteList::DeleteAllSprites()
{
	Sprite^ spriteWalker = head;

	while (spriteWalker != nullptr)
	{
		DeleteSprites(spriteWalker);
		spriteWalker = spriteWalker->Next;
	}
}

// delete a single sprite from a spritelist that is being passed in
void SpriteList::DeleteSprites(Sprite^ spriteToDelete)
{
	Sprite^ spriteWalker = head;
	if (spriteWalker == tail)
	{
		head = nullptr;
		tail = nullptr;
	}
	else if (spriteToDelete == spriteWalker)
	{
		head = spriteWalker->Next;
	}
	else
	{
		while (spriteWalker->Next != spriteToDelete)
		{
			spriteWalker = spriteWalker->Next;
		}
		spriteWalker->Next = spriteToDelete->Next;
		if (spriteToDelete == tail)
		{
			tail = spriteWalker;
		}
	}
}

// delete a single sprite from a spritelist that is being passed at the integer value position
void SpriteList::KillSingleSprite(int spriteToKill)
{
	Sprite^ spriteWalker = head;

	int indexToKill = spriteToKill;
	int currentIndex = 0;
	do
	{
		if (currentIndex == indexToKill)
		{
			spriteWalker->isAlive = false;
		}
		spriteWalker = spriteWalker->Next;
		currentIndex++;
	} while (currentIndex < indexToKill + 1);
}

// delete all the sprites if their bool isalive is false
void SpriteList::DeleteDeadSprites() {
	Sprite^ spriteWalker = head;
	while (spriteWalker != nullptr)
	{
		if (!spriteWalker->isAlive)
		{
			DeleteSprites(spriteWalker);
		}
		spriteWalker = spriteWalker->Next;
	}
}

// draws the enemy sprite within the viewport area 
void SpriteList::DrawNPCInViewport(int xViewport, int yViewport)
{
	Sprite^ spriteWalker = head;

	while (spriteWalker != nullptr)
	{
		int newXPos = spriteWalker->xPos - xViewport;
		int newYPos = spriteWalker->yPos - yViewport;

		if (newXPos >= 0 && newYPos >= 0 && newXPos <= 100 * 32 && newYPos <= 50 * 32)
		{
			spriteWalker->DrawPlayerViewport(newXPos, newYPos);
		}
		spriteWalker = spriteWalker->Next;
	}
}

// sets each enemmy sprites x, y pos to a room 
void SpriteList::SetNPCLocation(int roomIndex)
{
	Sprite^ spriteWalker = head;
	while (spriteWalker != nullptr)
	{
		for (int i = 1; i < roomIndex; i++)
		{
			spriteWalker->setPlayerStart(i);
			spriteWalker = spriteWalker->Next;
		}

	}
}

//called from gamemanager, send sprite position
void SpriteList::ScanAndRoamTrack(int playerX, int playerY)
{
	Sprite^ spriteWalker = head;
	while (spriteWalker != nullptr)
	{

		//scan, which will change FSM
		spriteWalker->Scan(playerX, playerY);

		//set direction based on state
		if (spriteWalker->getSpriteFSM() == ROAMING)
		{
			spriteWalker->SpriteRandomMove();
		}

		if (spriteWalker->getSpriteFSM() == TRACKING)
		{
			spriteWalker->Track(playerX, playerY);
		}

		spriteWalker = spriteWalker->Next;
	}
}

// checking each sprite whether they have a collision with a non-walkable tile
void SpriteList::NPCTileCollision()
{
	Sprite^ spriteWalker = head;
	while (spriteWalker != nullptr)
	{
		//spriteWalker->SpriteRandomMove();

		if (!spriteWalker->Collision())
		{
			//move spriteWalker
			spriteWalker->Move();
			UpdateFrame();
		}
		else
		{
			spriteWalker->SpriteBounce();
		}
		spriteWalker = spriteWalker->Next;
	}
}

// rolling through the linked list getting each sprites position and returning a point
Point SpriteList::NPCSpritePosition(int spriteToFind)
{
	Sprite^ spriteWalker = head;
	int indexToFind = spriteToFind;
	int currentIndex = 0;

	do
	{
		if (currentIndex == indexToFind)
		{
			return spriteWalker->GetPoint();
		}
		spriteWalker = spriteWalker->Next;
		currentIndex++;
	} while (currentIndex < indexToFind + 1);

}

// rolling through the linked list, incrementing count and returning count 
int SpriteList::SpriteCount()
{
	int count = 0;

	Sprite^ spriteWalker = head;
	while (spriteWalker != nullptr)
	{
		count++;
		spriteWalker = spriteWalker->Next;
	}
	return count;
}

// rolling through the linked list and setting the velocity x,y to zero
void SpriteList::TestStopOnCollision()
{
	Sprite^ spriteWalker = head;
	while (spriteWalker != nullptr)
	{
		spriteWalker->xVel = 0;
		spriteWalker->yVel = 0;
		spriteWalker = spriteWalker->Next;
	}
}