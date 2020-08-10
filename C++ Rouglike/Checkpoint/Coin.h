/*
  Program name:        Rougelike
  Project file name:   Coin
  Date:                15/05/2020
  Language:            C++
  Platform:     Microsoft Visual Studio 2017 - 2019
  Purpose:			Coin Item Object	
  Description:      Inherits variables from ITEM class, holds points property, collision with coin will increase game points
  Known Bugs:        Nothing currently
*/

#pragma once

#include "Item.h"

ref class Coin : public Item
{
public:
	Coin(Graphics^ startCanvas, Random^ startRGen, Bitmap^ bitmap, Size clientSize, TileMap^ map);
	property int points;
};

