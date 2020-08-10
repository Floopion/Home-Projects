/*
  Program name:			Rougelike
  Project file name:	TileViewport.h
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				To specify the methods and variables needed, whether they are public or private.
  Description:			Header file for the TileViewport, contains the variables and methods needed that will be implemented within the .cpp file.
  Known Bugs:			Nothing currently
*/

#pragma once
#include "TileMap.h"
#include "Sprite.h"
#define TILE_WIDTH 32
#define COL_MAX 99
#define ROW_MAX 49

ref class TileViewport
{
private:
	// variables
	TileList^ tileList;
	TileMap^ map;
	int viewportTilesWide;
	int viewportTilesHigh;
	Graphics^ canvas;
	int col, row;
	int tileWidth;
	Sprite^ player;

public:
	// constructor
	TileViewport(int startX, int startY, int startTilesWide, int startTilesHigh,
		TileMap^ startMap, Graphics^ startCanvas, Sprite^ sprite);

	// methods
	void ViewportMove(int xMove, int yMove);
	void ViewportDraw();
	void BoundsChecking();
	void MoveOnPlayerLocation(int xPlayer, int yPlayer);

	// properties
	property int ViewportWorldX;
	property int ViewportWorldY;
	property int ViewportTileX;
	property int ViewportTileY;
};
