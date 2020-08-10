/*
  Program name:        Rougelike
  Project file name:   Item
  Date:                15/05/2020
  Language:            C++
  Platform:     Microsoft Visual Studio 2017 - 2019
  Purpose:			Item Object (Parent)
  Description:      Parent class of Banana, Coin, Potion
  Known Bugs:        Nothing currently
*/

#pragma once
#include "TileMap.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class Item
{
protected:
	//graphics and bitmap to draw
	Graphics^ canvas;
	Bitmap^ itemBitmap;

	//needed to randomly generate position relative to the room start tile
	Random^ rGen;

	//position of the room
	Point start;
	TileMap^ tile;

	//image specifications of the bitmap
	int frameWidth;
	int frameHeight;

public:
	//itemList linking
	Item^ Next;

	property int xPos;
	property int yPos;
	property bool isAlive;

	Item(Graphics^ startCanvas, Random^ startRGen, Bitmap^ bitmap, Size clientSize, TileMap^ map);

	//draw on screen
	void DrawPlayerViewport(int xViewport, int yViewport);

	//returns position of the item for collision calculation with sprite
	Point GetPoint();

	//sets the position of the item
	void setItemStart(int roomIndex);
};

