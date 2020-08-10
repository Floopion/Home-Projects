#include "Banana.h"
//child class of Item
Banana::Banana(Graphics^ startCanvas, Random^ startRGen, Bitmap^ bitmap, Size clientSize, TileMap^ map) : Item(startCanvas, startRGen, bitmap, clientSize, map)
{
	healStrength = 100;
}