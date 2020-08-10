#include "Coin.h"
//child class of Item
Coin::Coin(Graphics^ startCanvas, Random^ startRGen, Bitmap^ bitmap, Size clientSize, TileMap^ map) : Item(startCanvas, startRGen, bitmap, clientSize, map)
{
	points = 100;
}