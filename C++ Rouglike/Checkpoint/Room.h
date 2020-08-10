/*
  Program name:        Pikachu Rougelike
  Project file name:   Room.h
  Date:                15/05/2020
  Language:            C++
  Platform:			   Microsoft Visual Studio 2017 - 2019
  Purpose:			   To handle all the individual room dimesnions.
  Description:         This class holds each rooms number in the list, dimensions, position in the world
					   and the position of the rooms center tile.
  Known Bugs:          -
*/
#pragma once


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
ref class Room
{
private:
	Random^ rGen;

public:
	property int xTile;
	property int yTile;
	property int tileWidth;
	property int tileHeight;
	property int xCenterTile;
	property int yCenterTile;

	Room(Random^ startRGen);
};

