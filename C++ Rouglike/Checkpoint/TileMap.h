/*
  Program name:			Rougelike
  Project file name:	TileMap.h
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				This is the Dungeon Class, to specify the methods and variables needed, whether they are public or private.
  Description:			Header file for the TileMap, contains the variables and methods needed that will be implemented within the .cpp file.
  Known Bugs:			Nothing currently
*/

#pragma once
#include "TileList.h"
#include "RoomList.h"
#define TILE_WIDTH 32

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

ref class TileMap
{
private:
	// variables
	TileList^ tileList;
	Room^ room;
	RoomList^ roomList;
	array<int, 2>^ map;
	Graphics^ canvas;
	Random^ rGen;
	int nCols;
	int nRows;
	int row;
	int col;
	Point l1;
	Point r1;
	Point l2;
	Point r2;
	//Pen^ pen;

public:
	// constructor
	TileMap(TileList^ startTileList, Graphics^ startCanvas, Random^ random, int startNCols, int startNRows);

	// methods
	void SetMapEntry(int col, int row, int tileIndex);
	int GetMapEntry(int col, int row);
	Bitmap^ GetMapCellBitmap(int col, int row);
	void ResetDrawMap();
	void DrawMap();
	void DrawRoom();
	bool TileListIsWalkeable(int col, int row);
	bool TileListIsEndTile(int col, int row);
	void CreateRooms();
	Point StartPoint(int roomIndex);
	void CreateCorridor();
	bool RoomCollisions(Room^ check, int currentRoom);
	bool CheckOverlap();

	// properties
	property int roomNumber;

};
