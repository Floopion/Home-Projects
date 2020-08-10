/*
  Program name:        Pikachu Rougelike
  Project file name:   Room.cpp
  Date:                15/05/2020
  Language:            C++
  Platform:			   Microsoft Visual Studio 2017 - 2019
  Purpose:			   To handle all the individual room dimesnions.
  Description:         This class holds each rooms number in the list, dimensions, position in the world
					   and the position of the rooms center tile.
  Known Bugs:          -
*/

#include "Room.h"

// The constructor assigns the room a random size and start postion. It then finds where its center tile is placed.
Room::Room(Random^ startRGen) 
{
	rGen = startRGen;	
	xTile = rGen->Next(3, 77);
	yTile = rGen->Next(3, 27);
	tileWidth = rGen->Next(8, 17);
	tileHeight = rGen->Next(8, 17);
	xCenterTile = xTile + tileWidth / 2;
	yCenterTile = yTile + tileHeight / 2;
}

