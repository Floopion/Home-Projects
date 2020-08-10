#include "GameManager.h"

GameManager::GameManager(Graphics^ startCanvas, Random^ startRGen, Size clientSize)
{
	//initialise form specs
	canvas = startCanvas;
	rGen = startRGen;
	clientWidth = clientSize.Width;
	clientHeight = clientSize.Height;
	formSize = clientSize;

	gamePoints = 0;
	dunegeonLvl = 1;

	//tile bitmaps loaded + added to tileList Array
	ground = gcnew Bitmap("ground.png");
	wall = gcnew Bitmap("wall.png");
	water = gcnew Bitmap("exit.png");

	tileList = gcnew TileList(3);

	tileList->SetTileArrayEntry(0, gcnew Tile(wall));
	tileList->SetTileArrayEntry(1, gcnew Tile(ground));
	tileList->SetTileArrayEntry(2, gcnew Tile(water));

	//tileMap Created
	tileMap = gcnew TileMap(tileList, canvas, rGen, 300, 200);
	tileMap->roomNumber = 4;

	//viewPort Created
	viewport = gcnew TileViewport(0, 0, 59, 31, tileMap, canvas, sprite);

	//Screen
	visibleScreen = EScreen::MENU; //set to menu initially

	//SpriteList
	spriteList = gcnew SpriteList();

	//Potion:: Item List
	potionList = gcnew ItemList();
	coinList = gcnew ItemList();
	bananaList = gcnew ItemList();
}

//on form load
void GameManager::StartGame()
{
	loadSpriteSheets();
	//creates screenManager and battleManager
	screenManager = gcnew ScreenManager(canvas, rGen, formSize);
	battleManager = gcnew BattleManager(rGen);

	//collision
	sprite->Collision();

	//load npc sprites
	LoadNPCSprite();

	//loads items
	loadItemBitmaps();
}

void GameManager::loadItemBitmaps()
{
	//bitmaps of items
	Bitmap^ coinBitmap = gcnew Bitmap("coin.bmp");
	Bitmap^ bananaBitmap = gcnew Bitmap("banana.bmp");
	Bitmap^ potionBitmap = gcnew Bitmap("potion.bmp");

	//make transaparent
	Color transparentColor = coinBitmap->GetPixel(0, 0);
	coinBitmap->MakeTransparent(transparentColor);
	Color transparentColor2 = bananaBitmap->GetPixel(0, 0);
	bananaBitmap->MakeTransparent(transparentColor2);
	Color transparentColor3 = potionBitmap->GetPixel(0, 0);
	potionBitmap->MakeTransparent(transparentColor3);

	//Creates 3 of each item
	for (int i = 0; i < 3; i++)
	{
		Banana^ banana = gcnew Banana(canvas, rGen, bananaBitmap, formSize, tileMap);
		bananaList->AddItem(banana);
	}

	for (int i = 0; i < 3; i++)
	{
		SuperPotion^ superPotion = gcnew SuperPotion(canvas, rGen, potionBitmap, formSize, tileMap);
		potionList->AddItem(superPotion);
	}

	for (int i = 0; i < 3; i++)
	{
		Coin^ coin = gcnew Coin(canvas, rGen, coinBitmap, formSize, tileMap);
		coinList->AddItem(coin);
	}
}

// called from StartGame to load pikachu bitmaps
void GameManager::loadSpriteSheets()
{
	Bitmap^ n = gcnew Bitmap("pika-n.bmp");
	Bitmap^ ne = gcnew Bitmap("pika-ne.bmp");
	Bitmap^ e = gcnew Bitmap("pika-e.bmp");
	Bitmap^ se = gcnew Bitmap("pika-se.bmp");
	Bitmap^ s = gcnew Bitmap("pika-s.bmp");
	Bitmap^ sw = gcnew Bitmap("pika-sw.bmp");
	Bitmap^ w = gcnew Bitmap("pika-w.bmp");
	Bitmap^ nw = gcnew Bitmap("pika-nw.bmp");

	//added to array of bitmaps
	array<Bitmap^>^ spriteImages = gcnew array<Bitmap^>(MAX_DIRECTIONS);

	spriteImages[ESpriteDirections::N] = n;
	spriteImages[ESpriteDirections::NE] = ne;
	spriteImages[ESpriteDirections::E] = e;
	spriteImages[ESpriteDirections::SE] = se;
	spriteImages[ESpriteDirections::S] = s;
	spriteImages[ESpriteDirections::SW] = sw;
	spriteImages[ESpriteDirections::W] = w;
	spriteImages[ESpriteDirections::NW] = nw;

	for (int i = 0; i < MAX_DIRECTIONS; i++)
	{
		Color transparentColor = spriteImages[i]->GetPixel(0, 0);
		spriteImages[i]->MakeTransparent(transparentColor);
	}
	sprite = gcnew Sprite(canvas, rGen, spriteImages, formSize, 3, tileMap);
}

//Creating a npc sprites, using spritelist class
void GameManager::LoadNPCSprite()
{
	//Bitmap images can be changed for emenmy spite
	Bitmap^ n = gcnew Bitmap("gengar-n.bmp");
	Bitmap^ ne = gcnew Bitmap("gengar-ne.bmp");
	Bitmap^ e = gcnew Bitmap("gengar-e.bmp");
	Bitmap^ se = gcnew Bitmap("gengar-se.bmp");
	Bitmap^ s = gcnew Bitmap("gengar-s.bmp");
	Bitmap^ sw = gcnew Bitmap("gengar-sw.bmp");
	Bitmap^ w = gcnew Bitmap("gengar-w.bmp");
	Bitmap^ nw = gcnew Bitmap("gengar-nw.bmp");

	//added to array of bitmaps
	array<Bitmap^>^ spriteImages = gcnew array<Bitmap^>(MAX_DIRECTIONS);

	spriteImages[ESpriteDirections::N] = n;
	spriteImages[ESpriteDirections::NE] = ne;
	spriteImages[ESpriteDirections::E] = e;
	spriteImages[ESpriteDirections::SE] = se;
	spriteImages[ESpriteDirections::S] = s;
	spriteImages[ESpriteDirections::SW] = sw;
	spriteImages[ESpriteDirections::W] = w;
	spriteImages[ESpriteDirections::NW] = nw;

	for (int i = 0; i < MAX_DIRECTIONS; i++)
	{
		Color transparentColor = spriteImages[i]->GetPixel(0, 0);
		spriteImages[i]->MakeTransparent(transparentColor);
	}
	//creates 3 enemy sprites and adds to spritelist
	for (int i = 0; i < 3; i++)
	{
		Sprite^ npcSprite = gcnew Sprite(canvas, rGen, spriteImages, formSize, 3, tileMap);
		spriteList->AddSprite(npcSprite);

	}
}

/*
	Main method for running the game,
	Draw the viewport,
	Draw NPC`s,
	Check for NPC tile collsions,
	Set the viewport up with the player location.
	Check for any sprite collisions,
	Check FSM for player to see if it is in battle,
	if true, change to the battle screen and run the battle.
*/
void GameManager::RunGame()
{
	viewport->ViewportDraw();
	viewport->MoveOnPlayerLocation(sprite->xPos, sprite->yPos);

	//draw Items and sprites
	potionList->DrawItemInViewport(viewport->ViewportWorldX, viewport->ViewportWorldY);
	coinList->DrawItemInViewport(viewport->ViewportWorldX, viewport->ViewportWorldY);
	bananaList->DrawItemInViewport(viewport->ViewportWorldX, viewport->ViewportWorldY);
	spriteList->DrawNPCInViewport(viewport->ViewportWorldX, viewport->ViewportWorldY);

	//scan and track / roam 
	spriteList->ScanAndRoamTrack(sprite->xPos, sprite->yPos);

	//check map collision
	spriteList->NPCTileCollision();

	sprite->PlayerLocationViewport();

	//check for sprites and items collision
	SpriteCollision();
	ItemCollision();

	//check if player has reached stairs
	if (sprite->EndTileCollision())
	{
		GenerateNewRound();
	}

	//loads prebattle screen if the player sprite is in BATTLING state and initiates battle methods
	if (sprite->getSpriteFSM() == BATTLING)
	{
		screenManager->PreBattleScreen();
		StartBattle();
		battleManager->battleIsRunning = true;
	}
	else
	{
		ScreenChange(GAME);
		battleManager->battleIsRunning = false;
	}
}

/*
	Method to mnove the player sprite, only moves if there is no collsion,
	checks th sprite bounds,
	Updates sprite frame to show correct image,
	Sets the viewport to correctly folly the sprite.
*/
void GameManager::SpriteMove()
{
	if (!sprite->Collision()) {
		sprite->Move();
	}

	sprite->PlayerWorldBoundCheck();
	sprite->UpdateFrame();
}

//resets the entire dungeon and increments player points and increases difficulty
void GameManager::GenerateNewRound()
{
	//increase poitns
	gamePoints += 500;
	//increments dungeon level
	dunegeonLvl++;
	//increase the hit chance
	battleManager->move4Chance *= ENEMY_ATTACK_INCREASE;
	battleManager->move5Chance *= ENEMY_ATTACK_INCREASE;
	battleManager->move6Chance *= ENEMY_ATTACK_INCREASE;

	//reset dungeon rooms
	tileMap->ResetDrawMap();
	tileMap->DrawMap();
	tileMap->CreateRooms();
	tileMap->DrawRoom();
	tileMap->CreateCorridor();
	//delete sprites
	spriteList->DeleteAllSprites();
	LoadNPCSprite();
	//set sprites again
	sprite->setPlayerStart(0);
	spriteList->SetNPCLocation(ROOM_NUMBER);
	//delete items
	potionList->DeleteAllItem();
	bananaList->DeleteAllItem();
	coinList->DeleteAllItem();
	loadItemBitmaps();
	//load all items
	potionList->SetItemLocation(ROOM_NUMBER);
	bananaList->SetItemLocation(ROOM_NUMBER);
	coinList->SetItemLocation(ROOM_NUMBER);
}

//runs on direction key down, to change the direction of the player sprite
void GameManager::Movement(ESpriteDirections movement)
{
	sprite->setSpriteDirections(movement);
}

//loads dungeon, rooms corridors and positions of sprites and items
void GameManager::LoadWorldMap()
{
	//dungeon
	tileMap->DrawMap();
	tileMap->CreateRooms();
	tileMap->DrawRoom();
	tileMap->CreateCorridor();
	//sprites
	sprite->setPlayerStart(0);
	spriteList->SetNPCLocation(ROOM_NUMBER);
	//items
	potionList->SetItemLocation(ROOM_NUMBER);
	coinList->SetItemLocation(ROOM_NUMBER);
	bananaList->SetItemLocation(ROOM_NUMBER);
}

//Switch staments accepting a string, changes the current screen depending on game state.
void GameManager::ScreenChange(EScreen changedScreen)
{
	visibleScreen = changedScreen;

	switch (visibleScreen)
	{
	case MENU:
		screenManager->MenuScreen();
		break;
	case GAME:
		screenManager->GameScreen(sprite->xPos, sprite->yPos, sprite->directionCornerX, sprite->directionCornerY, gamePoints, dunegeonLvl);
		break;
	case STATUS:
		screenManager->StatusScreen(sprite->hp);
		break;
	case BATTLE:
		screenManager->BattleScreen(60, 100, 100, 6, true, false, false, false, battleManager->move1, 0, 0);
		break;
	case PAUSE:
		screenManager->PauseScreen();
		break;
	case END:
		screenManager->EndScreen();
		break;
	default:
		break;
	}
}

//checks the positions of the sprites in the sprite list and determines whether there is a collision, If there is a collision with enemy sprites and triggers battles
void GameManager::SpriteCollision()
{
	//for loop through spritelist
	//send back spritewalkers position: x, y
	//then
	//send it to sprite->collision(x, y);
	//compare player sprite against the otherSprite

	for (int i = 0; i < spriteList->SpriteCount(); i++)
	{
		if (sprite->SpriteCollision(spriteList->NPCSpritePosition(i))) //if true
		{
			//sets the sprite number as the index of the sprite collided with. this will be used to delete the sprite after battle
			battleManager->enemySpriteNumber = i;
			//changes the FSM of the player sprite to battling, this will trigger the battle screen in GAMERUN
			sprite->setSpriteFSM(BATTLING);
		}
	}
}

//checks the positions of the items in the items list and determines whether there is a collision it triggers effect and kills, deletes the sprite as they are "Consumed"
void GameManager::ItemCollision()
{
	for (int i = 0; i < potionList->ItemCount(); i++)
	{
		if (sprite->ItemCollision(potionList->ItemPosition(i))) //if true
		{
			//collision ->  do something to 
			potionList->KillSingleItem(i);
			//go through the sprite list and delete the sprites that are "isAlive = false"
			potionList->DeleteDeadItems();
			sprite->hp += 50;
		}
	}

	for (int i = 0; i < bananaList->ItemCount(); i++)
	{
		if (sprite->ItemCollision(bananaList->ItemPosition(i))) //if true
		{

			bananaList->KillSingleItem(i);
			//go through the sprite list and delete the sprites that are "isAlive = false"
			bananaList->DeleteDeadItems();
			battleManager->move1Chance *= 1.1;
			battleManager->move2Chance *= 1.1;
			battleManager->move3Chance *= 1.1;
		}
	}

	for (int i = 0; i < coinList->ItemCount(); i++)
	{
		if (sprite->ItemCollision(coinList->ItemPosition(i))) //if true
		{
			//collision ->  do something to 
			coinList->KillSingleItem(i);
			//go through the sprite list and delete the sprites that are "isAlive = false"
			coinList->DeleteDeadItems();
			//points
			gamePoints += 100;
		}
	}
}

//Get Method for the screen
EScreen GameManager::GetVisibleScreen()
{
	return visibleScreen;
}

//initiates the battle on collision
void GameManager::StartBattle()
{
	//load variables to battleclass
	ScreenChange(BATTLE);
	battleManager->StartBattle(sprite->hp);
}

//runs battle on timer2 tick
void GameManager::RunBattle()
{
	//run on timer 2 tick
	battleManager->RunBattleRound();
	//update screen
	screenManager->BattleScreen(battleManager->timerCount, battleManager->hpPlayer, battleManager->hpNPC, battleManager->roundCount, battleManager->playerTurn, battleManager->attackHit, battleManager->battleEnd, battleManager->playerWin, battleManager->roundMove, battleManager->roundMoveDmg, battleManager->roundMoveChance);
	if (battleManager->battleEnd == true)
	{
		EndBattle();
	}
}

//if the battle has ended with the death of player
void GameManager::EndBattle()
{
	//run when battleends 
		//condition to check whether player has won
	if (battleManager->playerWin == true)
	{
		//if player has won, go through sprite list and turn "isAlive" bool to false for the enemy sprite we just battled
		spriteList->KillSingleSprite(battleManager->enemySpriteNumber);
		//go through the sprite list and delete the sprites that are "isAlive = false"
		spriteList->DeleteDeadSprites();

		//increase points
		gamePoints += 100;

		//update playerHP
		sprite->hp = battleManager->hpPlayer;

		//change sprite FSM to moving
		sprite->setSpriteFSM(MOVING);
		//change screen back to game
		ScreenChange(GAME);
	}
	else
	{
		ScreenChange(END);
	}
}