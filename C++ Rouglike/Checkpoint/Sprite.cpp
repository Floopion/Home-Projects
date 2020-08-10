/*
  Program name:        Rougelike
  Project file name:   Sprite.h
  Date:                15/05/2020
  Language:            C++
  Platform:			   Microsoft Visual Studio 2017 - 2019
  Purpose:			   Holds all of the information for the player, and NPC characters.
  Description:		   The sprite class has all the character states, sprites, collision methods, and
					   poistions / sizes.
  Known Bugs:		   - NPC sprites sometimes hang when trying to walk diagonally within and entering corridors.
					   - Occasionally coin collision and stair collsion can be unpredictable / undetected.
					   - If items spawn in the top row of tiles in a room, occassionally player collsion wont detect.
					   - Player collsion on corridors can be incosistant when moving east.
					   - NPC Sprite sheet refuses to cut frames consistantly.
*/

#include "Sprite.h"

Sprite::Sprite(Graphics^ startCanvas, Random^ startRGen, array<Bitmap^>^ startSpriteSheets, Size clientSize, int startNFrames, TileMap^ map)
{
	canvas = startCanvas;
	rGen = startRGen;
	spriteSheets = startSpriteSheets;
	nFrames = startNFrames;
	pen = gcnew Pen(Color::Black, 3);
	tile = map;

	//need to adjust frame sizes
	frameHeight = spriteSheets[0]->Height;
	frameWidth = (int)spriteSheets[0]->Width / nFrames;
	//need to adjust frame number
	currentFrame = rGen->Next(nFrames);

	xVel = 15;
	yVel = 15;

	xPos = 0;
	yPos = 0;

	spriteDirections = ESpriteDirections::E;
	spriteFSM = ESpriteFSM::TRACKING;

	velocityDirections = gcnew array<Point^>(MAX_DIRECTIONS);
	velocityDirections[0] = Point(0, -1);	//n
	velocityDirections[1] = Point(1, -1);	//ne
	velocityDirections[2] = Point(1, 0);	//e
	velocityDirections[3] = Point(1, 1);	//se
	velocityDirections[4] = Point(0, 1);	//s
	velocityDirections[5] = Point(-1, 1);	//sw
	velocityDirections[6] = Point(-1, 0);	//w
	velocityDirections[7] = Point(-1, -1);	//nw
	//need to apply right sprite sheet

	clientWidth = clientSize.Width;
	clientHeight = clientSize.Height;

	isAlive = true;

	hp = 100;

	Next = nullptr;
}

//get front left corner of sprite depending on the direction it is facing
void Sprite::GetDirectionCorner()
{
	int newXPos = xPos + (xVel * velocityDirections[spriteDirections]->X);
	int newYPos = yPos + (yVel * velocityDirections[spriteDirections]->Y);

	switch (spriteDirections)
	{
	case N:
		directionCornerX = newXPos;
		directionCornerY = newYPos;
		break;
	case S:
		directionCornerX = newXPos + frameWidth;
		directionCornerY = newYPos + frameHeight;
		break;
	case W:
		directionCornerX = newXPos;
		directionCornerY = newYPos + frameHeight;
		break;
	case E:
		directionCornerX = newXPos + frameWidth;
		directionCornerY = newYPos;
		break;
	case NE:
		directionCornerX = newXPos + frameWidth;
		directionCornerY = newYPos;
		break;
	case SE:
		directionCornerX = newXPos + frameWidth;
		directionCornerY = newYPos + frameHeight;
		break;
	case NW:
		directionCornerX = newXPos;
		directionCornerY = newYPos;
		break;
	case SW:
		directionCornerX = newXPos;
		directionCornerY = newYPos + frameHeight;
		break;
	default:
		break;
	}
}

/* This method accesses the sprites directional enus and sets is new position
depending on set velocity. Thie velocity hase been corrected for diagonal movement
*/
void Sprite::Move()
{
	//move sprite depending on current sprite direction
	if (spriteDirections == NE || spriteDirections == SE || spriteDirections == NW || spriteDirections == SW)
	{
		yPos += yVel * velocityDirections[spriteDirections]->Y;
		xPos += xVel * velocityDirections[spriteDirections]->X;
	}
	else
	{
		yPos += yVel * velocityDirections[spriteDirections]->Y;
		xPos += xVel * velocityDirections[spriteDirections]->X;
	}

	
	xTile = xPos / TILE_SIZE;
	yTile = yPos / TILE_SIZE;
	GetDirectionCorner();
}

//Create a new rectangle with the cuurent frames bounds. Draw everything to the canvas including a black rectangle
//around thhe player (This is for testing collision during dev)
void Sprite::Draw()
{
	Rectangle drawRect = Rectangle(currentFrame * frameWidth, 0, frameWidth, frameHeight);
	canvas->DrawImage(spriteSheets[spriteDirections], xPos, yPos, drawRect, GraphicsUnit::Pixel);
}

//Increments the number of frames so that the right part of the sprite sheet is shown.
void Sprite::UpdateFrame()
{
	currentFrame = (currentFrame + 1) % nFrames;
}


// Draws the player within the viewport
void Sprite::DrawPlayerViewport(int xViewport, int yViewport)
{
	int startY = 0;
	Rectangle drawRect = Rectangle(currentFrame * frameWidth, startY, frameWidth, frameHeight);
	canvas->DrawImage(spriteSheets[spriteDirections], xViewport, yViewport, drawRect, GraphicsUnit::Pixel);
}

void Sprite::PlayerLocationViewport()
{
	//checking: if the players x position is less than half 
	//e.g player is on the left side, lets them move freely 
	if (xPos < clientWidth / 2)
	{
		newXPos = xPos;
	}
	//checking: if the players x position + the panel center point is greater that the column * tiles width
	//e.g player is on the right side, lets them move freely
	else if (xPos + clientWidth / 2 > 100 * TILE_SIZE)
	{
		newXPos = xPos + clientWidth - 100 * TILE_SIZE;
	}
	//setting the players fixed x position to the center as they walk around the map
	else
	{
		newXPos = clientWidth / 2;
	}

	//checking: if the players y position is less than half 
	//e.g player is on top half, lets them move freely 
	if (yPos < clientHeight / 2)
	{
		newYPos = yPos;
	}
	//checking: if the players y position + the panel center point is greater that the row * tiles width
	//e.g player is on the bottom half, lets them move freely
	else if (yPos + clientHeight / 2 > 50 * TILE_SIZE)
	{
		newYPos = yPos + clientHeight - 50 * TILE_SIZE;
	}
	//setting the players fixed y position to the center as they walk around the map
	else
	{
		newYPos = clientHeight / 2;
	}

	DrawPlayerViewport(newXPos, newYPos);
}

void Sprite::PlayerWorldBoundCheck()
{
	//checking: if the player has reach the end of the world
	//setting new x and y positions
	if (xPos < 0)
	{
		xPos = 0;
	}
	if (xPos > 100 * TILE_SIZE - frameWidth)
	{
		xPos = 100 * TILE_SIZE - frameWidth;
	}
	if (yPos < 0)
	{
		yPos = 0;
	}
	if (yPos > 50 * TILE_SIZE - frameHeight)
	{
		yPos = 50 * TILE_SIZE - frameHeight;
	}
}

//find if the next tile is walkable, if it is, return collison as false, else return that a collsiion will occur
bool Sprite::Collision()
{
	GetDirectionCorner();

	if (tile->TileListIsWalkeable(directionCornerX / TILE_SIZE, directionCornerY / TILE_SIZE)) 
	{
		return false;
	}
	else 
	{
		return true;
	}
}

//check is the sprite is at the end tile, if true then game will return bool value that will be used to generate next round
bool Sprite::EndTileCollision()
{
	GetDirectionCorner();

	if (tile->TileListIsEndTile(directionCornerX / TILE_SIZE, directionCornerY / TILE_SIZE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//find the first room and put the player in the corner
void Sprite::setPlayerStart(int roomIndex) {
	
	start = tile->StartPoint(roomIndex);
	xPos = start.X;
	yPos = start.Y;
}

// return a sprites position in the world.
Point Sprite::GetPoint()
{
	return Point(xPos, yPos);
}

// Take all of the corner points of the sprites and construct a rectangle with them, check if these rectangles intersect, 
// if so, return true as a collision has occured.
bool Sprite::SpriteCollision(Point npcPoint)
{
	//player sprite point
	l1 = Point(xPos, yPos);
	r1 = Point(xPos + frameWidth, yPos + frameHeight);

	////npc sprite point
	l2 = Point(npcPoint.X, npcPoint.Y);
	r2 = Point(npcPoint.X + frameWidth, npcPoint.Y + frameHeight);

	Rectangle^ spriteOne = Rectangle(l1.X + 20, l1.Y, r1.X - l1.X - 5, r1.Y - l1.Y);
	Rectangle spriteTwo = Rectangle(l2.X, l2.Y, r2.X - l2.X, r2.Y - l2.Y);

	if (spriteOne->IntersectsWith(spriteTwo) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// check if the sprite has collided / intersects with an item ofbject. Return if this true if this has occured. 
bool Sprite::ItemCollision(Point itemPoint)
{
	l1 = Point(xPos, yPos);
	r1 = Point(xPos + frameWidth, yPos + frameHeight);

	////npc sprite point
	l2 = Point(itemPoint.X, itemPoint.Y);
	r2 = Point(itemPoint.X + 10, itemPoint.Y + 16);

	Rectangle^ spriteOne = Rectangle(l1.X + 20, l1.Y, r1.X - l1.X - 5, r1.Y - l1.Y);
	Rectangle item = Rectangle(l2.X, l2.Y, r2.X - l2.X, r2.Y - l2.Y);

	if (spriteOne->IntersectsWith(item) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Randomly change a sprites direction, so that NPC movment is less linear.
void Sprite::SpriteRandomMove()
{
	if (rGen->Next(5) < 1)
	{
		switch (rGen->Next(4))
		{
		case 0:
			setSpriteDirections(N);
			break;
		case 1:
			setSpriteDirections(S);
			break;
		case 2:
			setSpriteDirections(E);
			break;
		case 3:
			setSpriteDirections(W);
		}
	}
}

// Reverse the players movement. 
void Sprite::SpriteBounce()
{
	if (getSpriteDirections() == N)
	{
		setSpriteDirections(S);
	}
	else if (getSpriteDirections() == S)
	{
		setSpriteDirections(N);
	}
	else if (getSpriteDirections() == E)
	{
		setSpriteDirections(W);
	}
	else if (getSpriteDirections() == W)
	{
		setSpriteDirections(E);
	}
}

//Constantly see if the player is within a set ammount if tiles if it is, change its state.
void Sprite::Scan(int playerXPos, int playerYPos)
{
	int xDistance = playerXPos - xPos;
	int yDistance = playerYPos - yPos;
	if (xDistance < 7 * TILE_SIZE && xDistance > -7 * TILE_SIZE) // player is within range >> turn FSM to Tracking
	{
		if (yDistance < 7 * TILE_SIZE && yDistance > -7 * TILE_SIZE)
		{
			setSpriteFSM(TRACKING);
		}
	}
	else
	{
		setSpriteFSM(ROAMING);
	}
}

//While the plaer is within a set ammount of tiles, consistantly move towards it. 
void Sprite::Track(int playerXPos, int playerYPos)
{
	if (getSpriteFSM() == TRACKING)
	{
		//if the player is above
		int xDistance = playerXPos - xPos;
		int yDistance = playerYPos - yPos;
		if (xDistance == 0) {
			if (yDistance < 0) {
				setSpriteDirections(N);
			}
			else
			{
				setSpriteDirections(S);
			}
		}
		if (xDistance > 0)
		{
			if (yDistance == 0)
			{
				setSpriteDirections(E);
			}
			else if (yDistance > 0)
			{
				setSpriteDirections(SE);
			}
			else {
				setSpriteDirections(NE);
			}
		}
		if (xDistance < 0)
		{
			if (yDistance == 0)
			{
				setSpriteDirections(W);
			}
			else if (yDistance > 0)
			{
				setSpriteDirections(SW);
			}
			else {
				setSpriteDirections(NW);
			}
		}
	}
}