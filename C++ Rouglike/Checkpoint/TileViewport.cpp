/*
  Program name:			Rougelike
  Project file name:	TileViewport.cpp
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				Draws a scaled up part of the map that will fit the map
  Description:			Tile width and height will determind the area of which the view port will draw
  Known Bugs:			Nothing currently
*/

#include "TileViewport.h"


TileViewport::TileViewport(int startX, int startY, int startTilesWide, int startTilesHigh, TileMap^ startMap, Graphics^ startCanvas, Sprite^ sprite)
{
	ViewportWorldX = startX;
	ViewportWorldY = startY;
	ViewportTileX = ViewportWorldY / TILE_WIDTH;
	ViewportTileY = ViewportWorldY / TILE_WIDTH;
	viewportTilesWide = startTilesWide;
	viewportTilesHigh = startTilesHigh;
	map = startMap;
	canvas = startCanvas;
	player = sprite;
}

// moving the the viewport when the player moves
void TileViewport::ViewportMove(int xMove, int yMove)
{
	ViewportWorldX += xMove;
	ViewportWorldY += yMove;
	BoundsChecking();
	ViewportTileX = ViewportWorldX / TILE_WIDTH;
	ViewportTileY = ViewportWorldY / TILE_WIDTH;
}

// draw the viewport with in the form, from the starting x,y tile to the width and height of the tiles
void TileViewport::ViewportDraw()
{
	for (int c = ViewportTileX; c <= (ViewportTileX + viewportTilesWide); ++c)
	{
		for (int r = ViewportTileY; r <= (ViewportTileY + viewportTilesHigh); ++r)
		{
			Bitmap^ mapBitmap = map->GetMapCellBitmap(c, r);
			int screenX = (c - ViewportTileX) * TILE_WIDTH - ViewportWorldX % TILE_WIDTH;
			int screenY = (r - ViewportTileY) * TILE_WIDTH - ViewportWorldY % TILE_WIDTH;
			canvas->DrawImage(mapBitmap, screenX, screenY);
		}
	}
}

// checking the viewport bounds, if it goes over the border or not
void TileViewport::BoundsChecking()
{
	if (ViewportWorldX < 0)
	{
		ViewportWorldX = 0;
	}
	if (ViewportWorldX > (COL_MAX - viewportTilesWide) * TILE_WIDTH)
	{
		ViewportWorldX = (COL_MAX - viewportTilesWide) * TILE_WIDTH;
	}
	if (ViewportWorldY < 0)
	{
		ViewportWorldY = 0;
	}
	if (ViewportWorldY > (ROW_MAX - viewportTilesHigh) * TILE_WIDTH)
	{
		ViewportWorldY = (ROW_MAX - viewportTilesHigh) * TILE_WIDTH;
	}
}

// drawing the viewport on the players x,y position 
void TileViewport::MoveOnPlayerLocation(int xPlayer, int yPlayer)
{
	ViewportWorldX = xPlayer - ((viewportTilesWide * TILE_WIDTH) / 2);
	ViewportWorldY = yPlayer - ((viewportTilesHigh * TILE_WIDTH) / 2);

	BoundsChecking();
	ViewportTileX = ViewportWorldX / TILE_WIDTH;
	ViewportTileY = ViewportWorldY / TILE_WIDTH;
}