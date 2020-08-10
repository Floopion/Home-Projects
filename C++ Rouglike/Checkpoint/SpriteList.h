/*
  Program name:			Rougelike
  Project file name:	SpriteList.h
  Date:					15/05/2020
  Language:				C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				To specify the methods and variables needed, whether they are public or private.
  Description:			Header file for the SpriteList, contains the variables and methods needed that will be implemented within the .cpp file.
  Known Bugs:			Nothing currently
*/

#pragma once
#include "Sprite.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class SpriteList
{
private:
	//variables
	Sprite^ head;
	Sprite^ tail;

public:
	// constructor
	SpriteList(void);

	// methods
	void AddSprite(Sprite^ newSprite);
	void MoveSprites();
	void DrawSprites();
	void UpdateFrame();
	void DeleteSprites(Sprite^ spriteToDelete);
	void DeleteAllSprites();
	void DrawNPCInViewport(int xViewport, int yViewport);
	void SetNPCLocation(int roomIndex);
	void NPCTileCollision();
	Point NPCSpritePosition(int spriteToFind);
	int SpriteCount();
	void TestStopOnCollision();
	void KillSingleSprite(int spriteToKill);
	void DeleteDeadSprites();
	void ScanAndRoamTrack(int playerX, int playerY);
};

