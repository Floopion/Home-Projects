/*
  Program name:			Rougelike
  Project file name:	TileList.cpp
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				An array will hold types of tiles that are needed.
  Description:			Store a type of tile into an array that is like a pointer to return what tile is needed to be drawn (ground, wall, exit) tiles
  Known Bugs:			Nothing currently
*/

#include "TileList.h"

TileList::TileList(int startNTiles)
{
	nTiles = startNTiles;
	tileArray = gcnew array<Tile^>(nTiles);
}

// setting the arrays index to be the tile bitmap 
void TileList::SetTileArrayEntry(int tileIndex, Tile^ tileToEnter)
{
	tileArray[tileIndex] = tileToEnter;
}

// returning a type of tile bitmap that is in the arrays index 
Bitmap^ TileList::GetTileBitmap(int tileIndex)
{
	return tileArray[tileIndex]->TileBitmap;
}

// returning a bool, checking if the tileIndex being passed in is walkable or not
bool TileList::isTileWalkable(int tileIndex)
{
	int tileWall = 0;
	int tileGround = 1;
	int tileExit = 2;
	if (tileArray[tileIndex] == tileArray[tileGround]) //iswalker tile walkable == true
	{
		tileArray[tileIndex]->isWalkable = true;
	}
	else
	{
		tileArray[tileIndex]->isWalkable = false; // iswalker tile walkable == false
	}
	return tileArray[tileIndex]->isWalkable;
}

// returning a bool, checking if the tileIndex being passed is the exit tile, and if it is walkable
bool TileList::isEndTile(int tileIndex)
{
	int tileExit = 2;
	if (tileArray[tileIndex] == tileArray[tileExit]) // iswalker on end tile == true
	{
		tileArray[tileIndex]->isWalkable = true;
		return true;
	}
	else
	{
		return false;
	}
}
