#include "BattleManager.h"

BattleManager::BattleManager(Random^ startRGen)
{
	timerCount = 6;
	roundCount = 1;
	rGen = startRGen;

	//need to load hp from sprite
	playerWin = false;
	playerTurn = true;
	attackHit = false;
	battleEnd = false;

	//initial move specifications. chance changes as items are 
	move1 = "Tackle";
	move2 = "Quick Attack";
	move3 = "Thunderbolt";

	move4 = "Lick";
	move5 = "ShadowPunch";
	move6 = "DreamEater";

	move1Chance = 100;
	move2Chance = 75;
	move3Chance = 70;

	move4Chance = 35;
	move5Chance = 15;
	move6Chance = 10;

	move1Dmg = 15;
	move2Dmg = 40;
	move3Dmg = 50;

	move4Dmg = 30;
	move5Dmg = 70;
	move6Dmg = 90;
}

//reset battle when collision is detected .. player hp passed in from sprite through game manager
void BattleManager::StartBattle(int playerHP)
{
	roundCount = 1;
	timerCount = 6;
	battleEnd = false;
	hpPlayer = playerHP;
	attackHit = false;
	playerWin = false;
	playerTurn = true;
	hpNPC = 100;
}

//runs every timer2 tick (1second)
void BattleManager::RunBattleRound()
{
	//switch statement will carry out a calculation and progress the battle.
	switch (timerCount)
	{
	case 6: /// only first round
		break;

	case 5:
		break;

	case 4:
		break;

	case 3:
		//randomly selects a move
		if (playerTurn == true)
		{
			switch (rGen->Next(3))
			{
			case 2:
				roundMove = move1;
				roundMoveDmg = move1Dmg;
				roundMoveChance = move1Chance;
				break;
			case 1:
				roundMove = move2;
				roundMoveDmg = move2Dmg;
				roundMoveChance = move2Chance;
				break;
			case 0:
				roundMove = move3;
				roundMoveDmg = move3Dmg;
				roundMoveChance = move3Chance;
				break;
			}
		}
		else
		{
			switch (rGen->Next(3))
			{
			case 2:
				roundMove = move4;
				roundMoveDmg = move4Dmg;
				roundMoveChance = move4Chance;
				break;
			case 1:
				roundMove = move5;
				roundMoveDmg = move5Dmg;
				roundMoveChance = move5Chance;
				break;
			case 0:
				roundMove = move6;
				roundMoveDmg = move6Dmg;
				roundMoveChance = move6Chance;
				break;
			}
		}
		break;

	case 2:
		break;

	case 1:
		if (rGen->Next(100) < roundMoveChance)
		{
			//hit
			attackHit = true;
			if (playerTurn == true)
			{
				hpNPC = hpNPC - roundMoveDmg;
			}
			else
			{
				hpPlayer = hpPlayer - roundMoveDmg;
			}

			if (hpPlayer <= 0)
			{
				battleEnd = true;
				playerWin = false;
			}

			if (hpNPC <= 0)
			{
				battleEnd = true;
				playerWin = true;
			}
		}
		else
		{
			//miss
			attackHit = false;
		}
		break;

	case 0:
		//reset the timer and start new round
		timerCount = 5;
		roundCount++;
		playerTurn = !playerTurn;
		break;
	}
	timerCount -= 1;
}