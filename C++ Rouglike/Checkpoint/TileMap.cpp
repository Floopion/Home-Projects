/*
  Program name:			Rougelike
  Project file name:	TileMap.cpp
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				To implement the methods provided in the header file.
  Description:			Creating the constructor and impleting the methods needed, provided by the header file.
  Known Bugs:			Nothing currently
*/

#include "TileMap.h"

TileMap::TileMap(TileList^ startTileList, Graphics^ startCanvas, Random^ random, int startNCols, int startNRows)
{
	tileList = startTileList;
	canvas = startCanvas;
	rGen = random;
	nCols = startNCols;
	nRows = startNRows;
	map = gcnew array<int, 2>(startNCols, startNRows);
	l1 = Point(0, 0);
	r1 = Point(0, 0);
	l2 = Point(0, 0);
	r2 = Point(0, 0);
	//pen = gcnew Pen(Color::Black, 50);

	roomNumber = 4;
	row = 10 + rGen->Next(10);
	col = 10 + rGen->Next(10);

	roomList = gcnew RoomList(roomNumber);
}

// setting the 2D array entry col and row to be the tile index that needs to be drawn
void TileMap::SetMapEntry(int col, int row, int tileIndex)
{
	map[col, row] = tileIndex;
}

// returning an intger of the 2D array at col and row
int TileMap::GetMapEntry(int col, int row)
{
	return map[col, row];
}

// reseting the map and setting all the tiles to be tile 0 (ground tile)
void TileMap::ResetDrawMap()
{
	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0; j < nRows; j++)
		{
			SetMapEntry(i, j, 0);
		}
	}
}

// drawing the map, looping through col and row, getting the entry point, getting the tile for that entry point, then drawing the tile the entry point
void TileMap::DrawMap()
{
	for (int i = 0; i < nCols; i++)
	{
		for (int j = 0; j < nRows; j++)
		{
			int index = GetMapEntry(i, j);
			Bitmap^ tileBitmap = tileList->GetTileBitmap(index);
			canvas->DrawImage(tileBitmap, i * tileBitmap->Width, j * tileBitmap->Height);
		}
	}
}

// drawing rooms, for looping through the number of rooms, from the starting x,y tile to their width and height
// getting setting the entry points tile to be 1 (ground), then drawing the bitmap at the index
void TileMap::DrawRoom()
{
	// looping through number of rooms
	for (int r = 0; r < roomNumber; r++)
	{
		for (int i = roomList->GetRoom(r)->xTile; i < roomList->GetRoom(r)->xTile + roomList->GetRoom(r)->tileWidth; i++) // loop through rooms x tile to the rooms width
		{
			for (int j = roomList->GetRoom(r)->yTile; j < roomList->GetRoom(r)->yTile + roomList->GetRoom(r)->tileHeight; j++) // loop through rooms y tile to the rooms height
			{
				SetMapEntry(i, j, 1); // set the entry point to be tile 1 (ground)
				int index = GetMapEntry(i, j); // get the entry tile
				Bitmap^ tileBitmap = tileList->GetTileBitmap(index); // get the bitmap that is set to the currently entry point
				canvas->DrawImage(tileBitmap, i * tileBitmap->Width, j * tileBitmap->Height); // draw the tile
			}
		}
	}

}

// return a type of bitmap at the entry point of col and row that is being passed in
Bitmap^ TileMap::GetMapCellBitmap(int col, int row)
{
	int index = map[col, row];
	Bitmap^ tileBitmap = tileList->GetTileBitmap(index);
	return tileBitmap;
}

// return a bool at the entry point of col and row, checking if that tile is walkable
bool TileMap::TileListIsWalkeable(int col, int row)
{
	int index = map[col, row];
	bool tileBitmap = tileList->isTileWalkable(index);

	return tileBitmap;
}

// return a bool at the entry point of col and row, checking if that it is the exit tile and if tile is walkable
bool TileMap::TileListIsEndTile(int col, int row)
{
	int index = map[col, row];
	bool tileEndBitmap = tileList->isEndTile(index);

	return tileEndBitmap;
}

// creating the number off rooms and checking if they overlap, if overlap it true, keep creating a room till its not overlapping
void TileMap::CreateRooms()
{
	// create rooms and add it to the roomlist
	for (int i = 0; i < roomNumber; i++)
	{
		roomList->SetRoomArrayEntry(i, gcnew Room(rGen));
	}

	for (int i = 0; i < roomNumber; i++)
	{
		// check if the rooms and overlapping, whiles its true keep creating a room that is not overlapping 
		while (RoomCollisions(roomList->GetRoom(i), i))
		{
			roomList->SetRoomArrayEntry(i, gcnew Room(rGen));
		}
	}
}

// returns a point (x,y) of the room that is being passing in the parameters 
Point TileMap::StartPoint(int roomIndex)
{
	return Point(roomList->GetRoom(roomIndex)->xTile * TILE_WIDTH, roomList->GetRoom(roomIndex)->yTile * TILE_WIDTH);
}

// checking whether is it above or below, left or right and setting the entry point col and row to be tile 1 (ground)
void TileMap::CreateCorridor()
{
	for (int r = 0; r < roomNumber - 1; r++)
	{
		if (roomList->GetRoom(r)->yCenterTile < roomList->GetRoom(r + 1)->yCenterTile) {

			for (int j = 0; j < 2; j++)
			{
				for (int i = roomList->GetRoom(r)->yCenterTile; i <= roomList->GetRoom(r + 1)->yCenterTile + 1; i++)
				{
					SetMapEntry(roomList->GetRoom(r)->xCenterTile + j, i, 1);
					int index = GetMapEntry(roomList->GetRoom(r)->xCenterTile + j, i);
					Bitmap^ tileBitmap = tileList->GetTileBitmap(index);
					canvas->DrawImage(tileBitmap, roomList->GetRoom(r)->xCenterTile + j * tileBitmap->Width, i * tileBitmap->Height);
				}
			}
		}
		else
		{
			for (int j = 0; j < 2; j++)
			{
				for (int i = roomList->GetRoom(r)->yCenterTile; i >= roomList->GetRoom(r + 1)->yCenterTile; i--)
				{
					SetMapEntry(roomList->GetRoom(r)->xCenterTile + j, i, 1);
					int index = GetMapEntry(roomList->GetRoom(r)->xCenterTile + j, i);
					Bitmap^ tileBitmap = tileList->GetTileBitmap(index);
					canvas->DrawImage(tileBitmap, roomList->GetRoom(r)->xCenterTile + j * tileBitmap->Width, i * tileBitmap->Height);
				}
			}
		}
		if (roomList->GetRoom(r)->xCenterTile < roomList->GetRoom(r + 1)->xCenterTile) {

			for (int j = 0; j < 2; j++)
			{
				for (int i = roomList->GetRoom(r + 1)->xCenterTile; i >= roomList->GetRoom(r)->xCenterTile; i--)
				{
					SetMapEntry(i, roomList->GetRoom(r + 1)->yCenterTile + j, 1);
					int index = GetMapEntry(i, roomList->GetRoom(r + 1)->yCenterTile + j);
					Bitmap^ tileBitmap = tileList->GetTileBitmap(index);
					canvas->DrawImage(tileBitmap, i * tileBitmap->Width, roomList->GetRoom(r + 1)->yCenterTile + j * tileBitmap->Height);
				}
			}
		}
		else
		{
			for (int j = 0; j < 2; j++)
			{
				for (int i = roomList->GetRoom(r + 1)->xCenterTile; i <= roomList->GetRoom(r)->xCenterTile; i++)
				{
					SetMapEntry(i, roomList->GetRoom(r + 1)->yCenterTile + j, 1);
					int index = GetMapEntry(i, roomList->GetRoom(r + 1)->yCenterTile + j);
					Bitmap^ tileBitmap = tileList->GetTileBitmap(index);
					canvas->DrawImage(tileBitmap, i * tileBitmap->Width, roomList->GetRoom(r + 1)->yCenterTile + j * tileBitmap->Height);
				}
			}
		}
	}
	// setting the exit tile to be in the last room, spawns anywhere from the starting x,y position to the center point of room
	int x = roomList->GetRoom(roomNumber - 1)->xTile + rGen->Next(roomList->GetRoom(roomNumber - 1)->tileWidth / 2);
	int y = roomList->GetRoom(roomNumber - 1)->yTile + rGen->Next(roomList->GetRoom(roomNumber - 1)->tileHeight / 2);
	SetMapEntry(x, y, 2);
}

// checking current room and room against all the other rooms if they are overlapping
bool TileMap::RoomCollisions(Room^ check, int currentRoom)
{

	l1 = Point(check->xTile * TILE_WIDTH - TILE_WIDTH, check->yTile * TILE_WIDTH - TILE_WIDTH);
	r1 = Point((check->xTile * TILE_WIDTH + TILE_WIDTH) + (check->tileWidth * TILE_WIDTH), (check->yTile * TILE_WIDTH + TILE_WIDTH) + (check->tileHeight * TILE_WIDTH));

	// looping through all the rooms
	for (int i = 0; i < roomNumber; i++)
	{
		// checking all other rooms expect its self 
		if (i != currentRoom)
		{
			l2 = Point(roomList->GetRoom(i)->xTile * TILE_WIDTH - TILE_WIDTH, roomList->GetRoom(i)->yTile * TILE_WIDTH - TILE_WIDTH);
			r2 = Point((roomList->GetRoom(i)->xTile * TILE_WIDTH + TILE_WIDTH) + (roomList->GetRoom(i)->tileWidth * TILE_WIDTH), (roomList->GetRoom(i)->yTile * TILE_WIDTH + TILE_WIDTH) + (roomList->GetRoom(i)->tileHeight * TILE_WIDTH));

			// calling checkoverlap method, returns true or false value
			if (CheckOverlap()) {
				return true;
			}
		}
	}
	return false;
}

// checking if top left and bottom right corners of the rooms are overlaping
bool TileMap::CheckOverlap() {
	// If one rectangle is on left side of other
	if (l1.X >= r2.X || l2.X >= r1.X)
	{
		if (l1.Y <= r2.Y || l2.Y <= r1.Y)
		{
			return false;
		}
	}
	return true;
}