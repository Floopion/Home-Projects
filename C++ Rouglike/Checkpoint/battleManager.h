/*
  Program name:        Rougelike
  Project file name:   Battle Manager
  Date:                15/05/2020
  Language:            C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				Battle class manages the battle algorithm
  Description:			runs on timer2 ticker and calculates whether a attack is a miss or hit, as well as randomly selecting a move which is held in the class
						The Battle method runs in sync with the screenManager to update what is happening on the screen
  Known Bugs:			Nothing currently,
*/

#pragma once

#include "Sprite.h"
#include "SpriteList.h"
#include "ScreenManager.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Text;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Text;
ref class BattleManager
{
private:
	Random^ rGen;

public:
	BattleManager(Random^ startRGen);

	//public property to make it visible on screen >> make back to private
	property int hpPlayer;
	property int hpNPC;
	property int timerCount;
	property int roundCount;

	property bool attackHit;
	property bool playerWin;
	property bool playerTurn;
	property bool battleEnd;
	property bool battleIsRunning;

	//pokemon moves
	property String^ move1;
	property String^ move2;
	property String^ move3;
	property String^ move4;
	property String^ move5;
	property String^ move6;

	//holds the move of the round, can be a random player move or a random enemy move
	property String^ roundMove;
	property int roundMoveDmg;
	property int roundMoveChance;

	//move dmg
	property int move1Dmg;
	property int move2Dmg;
	property int move3Dmg;
	property int move4Dmg;
	property int move5Dmg;
	property int move6Dmg;

	//move hit chance
	property int move1Chance;
	property int move2Chance;
	property int move3Chance;
	property int move4Chance;
	property int move5Chance;
	property int move6Chance;

	//holds the index of the sprite that initiated the battle, it is returned in the end battle method of game manager to delete in the sprite list
	property int enemySpriteNumber;

	void StartBattle(int playerHP);
	void RunBattleRound();

};

