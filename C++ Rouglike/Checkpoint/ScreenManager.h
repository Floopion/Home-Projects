/*
  Program name:        Pikachu Rougelike
  Project file name:   ScreenManager.h
  Date:                15/05/2020
  Language:            C++
  Platform:			   Microsoft Visual Studio 2017 - 2019
  Purpose:			   To keep track of each Screen and Handle what is displayed in each screen.
  Description:         This class holds what is displayed whitin each screen, and where abouts the information
					   is drawn.
  Known Bugs:          - Centered content can be slightly off on differing screen sizes.
*/
#pragma once
#include "Sprite.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Text;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Text;

ref class ScreenManager
{
private:
	//form specs
	Graphics^ canvas;
	Size formSize;
	Pen^ pen;
	Rectangle boundary;

	//fonts + size difference
	Font^ font1;
	Font^ font2;
	Font^ font3;
	Font^ fontTitle;

	//brushes for colour
	SolidBrush^ whiteBrush;
	SolidBrush^ redBrush;
	SolidBrush^ blueBrush;
	SolidBrush^ yellowBrush;

public:
	ScreenManager(Graphics^ startCanvas, Random^ startRGen, Size clientSize);

	//different screens to draw
	void MenuScreen();
	void GameScreen(int spriteXPos, int spriteYPos, int cornerx, int cornery, int gamePoints, int dungeonLvl);
	void BattleScreen(int timerCount, int hpPlayer, int hpNPC, int roundCount, bool playerTurn, bool attackHit, bool gameEnd, bool playerWin, String^ roundMove, int roundMoveDmg, int roundMoveChance);
	void PauseScreen();
	void StatusScreen(int hp);
	void PreBattleScreen();
	void EndScreen();
};

