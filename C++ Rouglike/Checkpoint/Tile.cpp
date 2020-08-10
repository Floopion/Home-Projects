/*
  Program name:			Rougelike
  Project file name:	Tile.cpp
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				Saves a tile bitmap
  Description:			Takes in a tile and save that bitmap
  Known Bugs:			Nothing currently
*/

#include "Tile.h"

Tile::Tile(Bitmap^ startTileBitmap)
{
    TileBitmap = startTileBitmap;
}
