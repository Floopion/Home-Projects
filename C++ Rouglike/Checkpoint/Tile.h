/*
  Program name:			Rougelike
  Project file name:	Tile.h
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				To specify the methods and variables needed, whether they are public or private.
  Description:			Header file for the Tile, contains the variables and methods needed that will be implemented within the .cpp file.
  Known Bugs:			Nothing currently
*/

#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class Tile
{

public:
    // constructor
    Tile(Bitmap^ startTileBitmap);

    // properties
    property bool isWalkable;
    property Bitmap^ TileBitmap;
};

