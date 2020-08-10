/*
  Program name:        Pikachu Rougelike
  Project file name:   ScreenManager.cpp
  Date:                15/05/2020
  Language:            C++
  Platform:			   Microsoft Visual Studio 2017 - 2019
  Purpose:			   To keep track of each Screen and Handle what is displayed in each screen.
  Description:         This class holds what is displayed whitin each screen, and where abouts the information
					   is drawn.
  Known Bugs:          - Centered content can be slightly off on differing screen sizes.
*/
#include "ScreenManager.h"
#include "Sprite.h"


//Constructor assigns all the fonts, pen sizes, and brush colors.
ScreenManager::ScreenManager(Graphics^ startCanvas, Random^ startRGen, Size clientSize)
{
	canvas = startCanvas;
	formSize = clientSize;
	pen = gcnew Pen(Color::White);

	font1 = gcnew Font("Impact", 40);
	font2 = gcnew Font("Impact", 30);
	font3 = gcnew Font("Impact", 20);
	fontTitle = gcnew Font("Impact", 80);
	whiteBrush = gcnew SolidBrush(Color::White);
	redBrush = gcnew SolidBrush(Color::Red);
	blueBrush = gcnew SolidBrush(Color::BlueViolet);
	yellowBrush = gcnew SolidBrush(Color::Yellow);

}

// Draw all the text and positions for the start screen
void ScreenManager::MenuScreen()
{
	canvas->DrawString("ROGUE PIKACHU DUNGEON", fontTitle, redBrush, formSize.Width/2 - 600, formSize.Height/2 - 300);
	canvas->DrawString("MENU SCREEN", font1, whiteBrush, formSize.Width / 2 - 200, formSize.Height / 2-100);
	canvas->DrawString("Press ENTER to Start", font2, blueBrush, formSize.Width / 2 - 213, formSize.Height / 2);
	canvas->DrawString("(IN GAME)", font2, redBrush, formSize.Width / 2 - 130, formSize.Height / 2 + 150);
	canvas->DrawString("Press R for STATUS Screen", font2, whiteBrush, formSize.Width / 2 - 260, formSize.Height / 2 + 200);
	canvas->DrawString("Press SPACE for PAUSE", font2, whiteBrush, formSize.Width / 2 - 240, formSize.Height / 2 + 250);
	canvas->DrawString("Press ENTER for MENU SCREEN", font2, whiteBrush, formSize.Width / 2 - 280, formSize.Height / 2 + 300);
	canvas->DrawString("**Item effects in Status Screen", font2, blueBrush, formSize.Width / 2 - 285, formSize.Height / 2 + 350);
}

// Draw all the game points and dungeon level for the game screen screen
void ScreenManager::GameScreen(int spriteXPos, int spriteYPos, int cornerx, int cornery, int gamePoints, int dungeonLvl)
{
	canvas->DrawString("GAME", font1, whiteBrush, 50, 50);
	canvas->DrawString("DUNEGEON LEVEL : ", font3, redBrush, 70, 130);
	canvas->DrawString(dungeonLvl.ToString(), font3, redBrush, 300, 130);

	canvas->DrawString("GAME POINTS : ", font3, redBrush, 500, 130);
	canvas->DrawString(gamePoints.ToString(), font3, redBrush, 800, 130);
	
}

// Manage all the text for the battles depending on whose turn it is, and waht attack is randomly selected.
void ScreenManager::BattleScreen(int timerCount, int hpPlayer, int hpNPC, int roundCount, bool playerTurn, bool attackHit, bool battleEnd, bool playerWin, String^ roundMove, int roundMoveDmg, int roundMoveChance)
{
	if (battleEnd == false)
	{
		if (timerCount <= 5)
		{
			canvas->DrawString("BATTLE", font1, redBrush, 50, 50);
			canvas->DrawString("ROUND : ", font3, whiteBrush, 70, 130);
			canvas->DrawString(roundCount.ToString(), font3, redBrush, 170, 130);

			canvas->DrawString("ATTACK TURN : ", font3, whiteBrush, 400, 130);
			if (playerTurn == true)
			{
				canvas->DrawString("PLAYER", font3, yellowBrush, 600, 130);
			}
			else
			{
				canvas->DrawString("NPC", font3, yellowBrush, 600, 130);
			}

			canvas->DrawString("PLAYER HP : ", font3, redBrush, 70, 230);
			canvas->DrawString("NPC HP : ", font3, redBrush, 70, 260);
			if (hpPlayer > 0)
			{
				canvas->DrawString(hpPlayer.ToString(), font3, whiteBrush, 240, 230);
			}
			else
			{
				canvas->DrawString("0", font3, redBrush, 240, 230);
			}
			if (hpNPC > 0)
			{
				canvas->DrawString(hpNPC.ToString(), font3, whiteBrush, 240, 260);
			}
			else
			{
				canvas->DrawString("0", font3, redBrush, 240, 260);
			}
		}
		




		//what to print each timerCount
		switch (timerCount)
		{
		case 5:
			canvas->DrawString("BATTLE START ", font1, redBrush, 500, 260);
			break;

		case 4:
			canvas->DrawString("ROUND START ", font1, redBrush, 500, 260);
			break;

		case 3:
			canvas->DrawString("CHOOSING MOVE ", font1, redBrush, 450, 360);
			canvas->DrawString(timerCount.ToString(), font1, yellowBrush, 650, 560);
			break;

		case 2:
			canvas->DrawString("MOVE ", font1, redBrush, 400, 360);
			canvas->DrawString(roundMove, font1, blueBrush, 600, 360);
			canvas->DrawString(timerCount.ToString(), font1, yellowBrush, 650, 560);
			break;

		case 1:
			canvas->DrawString("READY", font1, redBrush, 600, 260);
			canvas->DrawString(timerCount.ToString(), font1, yellowBrush, 650, 560);
			break;

		case 0:
			if (attackHit == true)
			{
				canvas->DrawString("HIT!!", font1, blueBrush, formSize.Width/2 + 100, 360);
			}
			else
			{
				canvas->DrawString("MISS!!", font1, blueBrush, formSize.Width / 2 + 100, 360);
			}


			if (playerTurn == true)
			{
				canvas->DrawString("PLAYER ATTACK!!", font1, redBrush, formSize.Width / 2 -400, 360);
			}
			else
			{
				canvas->DrawString("WILD POKEMON ATTACK!!", font1, redBrush, formSize.Width / 2 -500, 360);
			}

			if (battleEnd == true)
			{
				canvas->DrawString("BATTLE ENDED!!", font1, redBrush, 700, 330);
				if (playerWin == true)
				{
					canvas->DrawString("PLAYER WINS!!", font1, redBrush, 500, 430);
				}
				else
				{
					canvas->DrawString("PLAYER FAINTED!!", font1, redBrush, 500, 430);
				}
			}

			break;
		}
	
	}
}

// Handle the text for the pause screen.
void ScreenManager::PauseScreen()
{
	canvas->DrawString("PAUSED", fontTitle, redBrush, formSize.Width/2 - 200, formSize.Height/2-100);
	canvas->DrawString("SPACE to UNPAUSE", font1, redBrush, formSize.Width / 2 - 225, formSize.Height / 2+30);
}


// Show the player how to restart if they have died.
void ScreenManager::EndScreen()
{
	canvas->DrawString("GAME OVER", fontTitle, redBrush, formSize.Width / 2 - 225, formSize.Height / 2 - 100);
	canvas->DrawString("PLAYER FAINTED!!", font1, redBrush, formSize.Width / 2 - 225, formSize.Height / 2 + 30);
	canvas->DrawString("PRESS Q TO TRY AGAIN!", font1, yellowBrush, formSize.Width / 2 - 225, formSize.Height / 2 + 130);
}


// Let player know a battle is starting
void ScreenManager::PreBattleScreen()
{
	canvas->DrawString("BATTLE!!!", fontTitle, redBrush, formSize.Width / 2 - 200, formSize.Height / 2 - 10);
}

//Show the player all of their stats
void ScreenManager::StatusScreen(int hp)
{
	canvas->DrawString("STATUS", font1, whiteBrush, 50, 50);
	canvas->DrawString("PIKACHU HP", font2, whiteBrush, 50, 150);
	canvas->DrawString(hp.ToString(), font2, whiteBrush, 300, 150);
	canvas->DrawString("ITEMS", font2, redBrush, 50, 250);
	canvas->DrawString("NAME", font2, whiteBrush, 200, 250);
	canvas->DrawString("EFFECT", font2, whiteBrush, 440, 250);
	canvas->DrawString("NAME", font2, whiteBrush, 200, 250);
	canvas->DrawString("BANANA", font3, yellowBrush, 200, 310);
	canvas->DrawString("COIN", font3, yellowBrush, 200, 360);
	canvas->DrawString("POTION", font3, yellowBrush, 200, 410);
	canvas->DrawString("Increase Attack Hit Chance", font3, blueBrush, 440, 310);
	canvas->DrawString("Increase Points +100", font3, blueBrush, 440, 360);
	canvas->DrawString("Recover 50 Health", font3, blueBrush, 440, 410);


	canvas->DrawString("Press E to return", font2, redBrush, 400, 50);

}