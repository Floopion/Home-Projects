/*
  Program name:			Rougelike
  Project file name:	TileList.h
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				To specify the methods and variables needed, whether they are public or private.
  Description:			Header file for the TileList, contains the variables and methods needed that will be implemented within the .cpp file.
  Known Bugs:			Nothing currently
*/

#pragma once
#include "Tile.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class TileList
{
private:
    // variables
    array<Tile^>^ tileArray;
    int nTiles;

public:
    // constructor 
    TileList(int startNTiles);

    // methods
    void SetTileArrayEntry(int tileIndex, Tile^ tileToEnter);
    Bitmap^ GetTileBitmap(int tileIndex);
    bool isTileWalkable(int	tileIndex);
    bool isEndTile(int tileIndex);
};

