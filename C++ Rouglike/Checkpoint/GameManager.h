/*
  Program name:        Rougelike
  Project file name:   Game Manager
  Date:                15/05/2020
  Language:            C++
  Platform:     Microsoft Visual Studio 2017 - 2019
  Purpose:				Manages the overall operations of the game.
						interacts with the Form, passing and calling methods from other classes.

						Form >>	GAMEMANAGER	>> ScreenManager
											>> BattleManager
											>> SpriteList
											>> Sprite
											>> Tilemap >> TileList >> Tile
											>> TileViewPort
											>> RoomList >> Room
											>> ItemList >> Item >> Banana
																>> Coin
																>> SuperPotion

  Description:      Core Functions are calculating the Collisions and running specific class methods on GAMERUN (ON TIMER1.Tick) and GAMESTART (ON Form.Load)
  Known Bugs:        Nothing currently
*/

#pragma once
#define ENEMY_ATTACK_INCREASE 1.1 // increases the hit chance of attacks by 10%
#define ROOM_NUMBER 4

#include "Sprite.h"
#include "SpriteList.h"
#include "ItemList.h"

#include "Banana.h"
#include "SuperPotion.h"
#include "Item.h"
#include "Coin.h"

#include "Tile.h"
#include "TileList.h"
#include "TileMap.h"
#include "TileViewport.h"
#include "ScreenManager.h"
#include "BattleManager.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//screens enum
public enum EScreen { MENU, GAME, STATUS, BATTLE, PAUSE, END };

ref class GameManager
{
private:
	//Sprites
	Sprite^ sprite;
	SpriteList^ spriteList;
	Bitmap^ spriteSheet;
	array<Bitmap^>^ spriteSheets;
	int nFrames;

	//Tiles
	Tile^ tile;
	TileList^ tileList;
	TileMap^ tileMap;

	Bitmap^ ground;
	Bitmap^ wall;
	Bitmap^ water;

	//Graphics + Random + Form Specs
	Graphics^ canvas;
	Random^ rGen;
	int clientWidth;
	int clientHeight;
	Size formSize;

	//gamestats
	int gamePoints;
	int dunegeonLvl;

	//ViewPort
	TileViewport^ viewport;

	//Collision
	Point directionCorner;

	//Screen
	EScreen visibleScreen;
	ScreenManager^ screenManager;

	//New Round
	int roundCount;
	int roomCount;
	int npcCount;

	//Items
	ItemList^ potionList;
	ItemList^ coinList;
	ItemList^ bananaList;

public:
	//Constructor
	GameManager(Graphics^ startCanvas, Random^ startRGen, Size clientSize);

	// runs on form Load
	void StartGame();
	void loadSpriteSheets();
	void loadItemBitmaps();
	void LoadNPCSprite();
	void LoadWorldMap();

	// runs when player reaches the endTile
	void GenerateNewRound();

	// runs on timer tick??
	void RunGame();
	void SpriteMove();
	void Movement(ESpriteDirections moveNumber); // pass key input to change sprite direction

	//screens
	void ScreenChange(EScreen changedScreen);
	EScreen GetVisibleScreen();

	//sprite collision
	void SpriteCollision();

	//item Collision
	void ItemCollision();

	//battle
	void StartBattle();
	void RunBattle();
	void EndBattle();

	//Battle
	BattleManager^ battleManager;

	property bool isAtEndTile;
};