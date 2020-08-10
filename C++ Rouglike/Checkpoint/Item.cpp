#include "Item.h"


//constructor
Item::Item(Graphics^ startCanvas, Random^ startRGen, Bitmap^ bitmap, Size clientSize, TileMap^ map)
{
	canvas = startCanvas;
	rGen = startRGen;
	frameHeight = bitmap->Height;
	frameWidth = bitmap->Width;
	tile = map;
	itemBitmap = bitmap;
	isAlive = true;
}

void Item::DrawPlayerViewport(int xViewport, int yViewport)
{
	canvas->DrawImage(itemBitmap, xViewport, yViewport);
}

Point Item::GetPoint()
{
	//returned to collision method in gameManager->Item Collision
	return Point(xPos, yPos);
}

void Item::setItemStart(int roomIndex)
{
	start = tile->StartPoint(roomIndex);
	//randomly generates in room
	xPos = start.X+rGen->Next(30,210);
	yPos = start.Y+rGen->Next(30,210);
}