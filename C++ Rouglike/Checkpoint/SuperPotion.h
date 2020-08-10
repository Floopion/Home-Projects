/*
  Program name:			Rougelike
  Project file name:	SuperPotion.h
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				Child class of item, is a potion
  Description:			SuperPotion (child) class is being inherited by the Item (parent) class, the child class only needs one extra variable that is different from the parent class.
  Known Bugs:			Nothing currently
*/

#pragma once
#include "Item.h"

ref class SuperPotion : public Item // superpotion is a type of item
{
public:
    // constructor
    SuperPotion(Graphics^ startCanvas, Random^ startRGen, Bitmap^ bitmap, Size clientSize, TileMap^ map);

    // properties
    property int healStrength;
};