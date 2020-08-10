/*
  Program name:        Rougelike
  Project file name:   Banana
  Date:                15/05/2020
  Language:            C++
  Platform:     Microsoft Visual Studio 2017 - 2019
  Purpose:			Banana Item Object
  Description:      Inherits variables from ITEM class, collision with the Banana will increase attack power by 10%
  Known Bugs:        Nothing currently
*/

#pragma once

#include "Item.h"

ref class Banana : public Item
{
public:
	Banana(Graphics^ startCanvas, Random^ startRGen, Bitmap^ bitmap, Size clientSize, TileMap^ map);
	property int healStrength;
};


