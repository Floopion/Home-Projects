/*
  Program name:			Rougelike
  Project file name:	SuperPotion.cpp
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				Child class of item, is a potion
  Description:			SuperPotion (child) class is being inherited by the Item (parent) class, the child class only needs one extra variable that is different from the parent class.
  Known Bugs:			Nothing currently
*/

#include "SuperPotion.h"

// calling the parent class to initialize the parameters being passed in
SuperPotion::SuperPotion(Graphics^ startCanvas, Random^ startRGen, Bitmap^ bitmap, Size clientSize, TileMap^ map) : Item(startCanvas, startRGen, bitmap, clientSize, map)
{
    healStrength = 50;
}