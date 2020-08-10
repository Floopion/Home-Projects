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

#pragma once
#include "TileMap.h"
#define MAX_DIRECTIONS 8
#define SPRITE_SIZE 31
#define TILE_SIZE 32

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public enum ESpriteDirections { N, NE, E, SE, S, SW, W, NW };
public enum ESpriteFSM {IDLE,BATTLING,MOVING,ROAMING,TRACKING};

ref class Sprite
{
private:
	//form specs
	Graphics^ canvas;
	Random^ rGen;

	Bitmap^ spriteSheet;
	array<Bitmap^>^ spriteSheets;
	Pen^ pen;

	TileMap^ tile;

	int nFrames;
	int currentFrame;

	int frameWidth;
	int frameHeight;

	int clientWidth;
	int clientHeight;

	int xLocation;
	int yLocation;

	int newXPos;
	int newYPos;

	/*int directionCornerX;
	int directionCornerY;*/

	Point start;
	Point l1;
	Point r1;
	Point l2;
	Point r2;

	ESpriteFSM spriteFSM;
	ESpriteDirections spriteDirections;
	array<Point^>^ velocityDirections;

public:
	Sprite^ Next;

	//public property to make it visible on screen >> make back to private
	property int directionCornerX;
	property int directionCornerY;

	property int xPos;
	property int yPos;

	property int xVel;
	property int yVel;

	property int xTile;
	property int yTile;

	property bool isAlive;

	property int hp;

	Sprite(Graphics^ startCanvas, Random^ startRGen, array<Bitmap^>^ startSpriteSheets, Size clientSize, int startNFrames, TileMap^ map);

	void Draw();
	void Move();
	void UpdateFrame();
	void DrawPlayerViewport(int xViewport, int yViewport);
	void PlayerLocationViewport();
	void PlayerWorldBoundCheck();
	void GetDirectionCorner();
	bool Collision();
	bool EndTileCollision();
	void setPlayerStart(int roomIndex);
	Point GetPoint();
	bool SpriteCollision(Point npcPoint);
	bool ItemCollision(Point itemPoint);
	void SpriteRandomMove();
	void SpriteBounce();

	void Scan(int playerXPos, int playerYPos);
	void Track(int playerXPos, int playerYPos);
 
	//properties
	int setSpriteFSM(ESpriteFSM state) { spriteFSM = state; return spriteFSM; }
	int getSpriteFSM() { return spriteFSM; }
	int setSpriteDirections(ESpriteDirections dir) { spriteDirections = dir; return spriteDirections; }
	int getSpriteDirections() { return spriteDirections; }

};

