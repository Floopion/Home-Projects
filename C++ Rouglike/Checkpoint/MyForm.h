/*
  Program name:        Pikachu Rougelike
  Project file name:   MyForm.h
  Date:                15/05/2020
  Language:            C++
  Platform:			   Microsoft Visual Studio 2017 - 2019
  Purpose:			   To handle all the key and form events
  Description:         This Class Handles what happens what happens when the
					   player pushes a key, it passes the game manager the nessacary draw
					   and random components and lets it know when to start a game.
  Known Bugs:          - Occasionally pushing the game restart key when the player is alive
						 causes timer tick slowdown.
*/
#pragma once
#include "Sprite.h"
#include "GameManager.h"

namespace Checkpoint {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		GameManager^ gameManager;
		Graphics^ startCanvas;
		Graphics^ bufferGraphics;
		Sprite^ sprite;
		Random^ startRGen;
		Bitmap^ bufferImage;
		Bitmap^ backgroundImage;
		Bitmap^ spriteImg;
		Color^ color;
		Brush^ brush;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Timer^ timer2;

	private: System::ComponentModel::IContainer^ components;
			 /// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::Timer1_Tick);
			// 
			// timer2
			// 
			this->timer2->Interval = 1000;
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::Timer2_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1960, 796);
			this->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Shown += gcnew System::EventHandler(this, &MyForm::MyForm_Shown);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown_1);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
		startCanvas = CreateGraphics();
		startRGen = gcnew Random;
		color = gcnew Color;
		brush = gcnew SolidBrush(Color::Black);
		bufferImage = gcnew Bitmap(Width, Height);
		//backgroundImage = gcnew Bitmap(brush,Width,Height);
		bufferGraphics = Graphics::FromImage(bufferImage);
		timer1->Enabled = false;

		gameManager = gcnew GameManager(bufferGraphics, startRGen, ClientSize);
		
	}

	// Second timer tells the game manager to run a battle, and stop the first timer which will
	// Stop the NPC`s moving in the background while you are battling
	private: System::Void Timer2_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		bufferGraphics->FillRectangle(Brushes::Black, 0, 0, Width, Height);
		gameManager->RunBattle();

		if (gameManager->GetVisibleScreen() == GAME)
		{
			timer1->Enabled = true;
		}
		startCanvas->DrawImage(bufferImage, 0, 0);
		if (gameManager->GetVisibleScreen() == END)
		{
			timer2->Enabled = false;
		}
	}

	
	// First timer tells the game Manager to run the NPC movment, if it detects that the player is 
	// Battling it will toggle the correct timer.
	private: System::Void Timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		//bufferGraphics->Clear(Color::Black);

		bufferGraphics->FillRectangle(Brushes::Black, 0, 0, Width, Height);
		gameManager->RunGame();
		startCanvas->DrawImage(bufferImage, 0, 0);


		//listening every tick if it is on battlescreen
		if (gameManager->GetVisibleScreen() == BATTLE)
		{
			timer2->Enabled = true;
			timer1->Enabled = false;
			bufferGraphics->FillRectangle(Brushes::Black, 0, 0, Width, Height);
		}
		else
		{
			timer2->Enabled = false;
		}
		
	}

	/* Key is down handles all the Key Press events.
	 - Switch statemet is encased in a check to disable player movement in the world if they are currently in a battle
	 - The game restart key is excluded in this as it runs when both a battle is finished and the game is finished so needs to fire when everything has stopped.
		it has also been encased in a check to stop accidental game restart during play.
	 */
	private: System::Void MyForm_KeyDown_1(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		
		bool move = false;

		if (!gameManager->battleManager->battleIsRunning) {
			switch (e->KeyData)
			{
				case Keys::NumPad8:
					sprite->setSpriteDirections(N);
					break;
				case Keys::NumPad9:
					sprite->setSpriteDirections(NE);
					break;
				case Keys::NumPad6:
					sprite->setSpriteDirections(E);
					break;
				case Keys::NumPad3:
					sprite->setSpriteDirections(SE);
					break;
				case Keys::NumPad2:
					sprite->setSpriteDirections(S);
					break;
				case Keys::NumPad1:
					sprite->setSpriteDirections(SW);
					break;
				case Keys::NumPad4:
					sprite->setSpriteDirections(W);
					break;
				case Keys::NumPad7:
					sprite->setSpriteDirections(NW);
					break;

				case Keys::Up:
					if (gameManager->GetVisibleScreen() == GAME)
					{
						gameManager->Movement(N);
						move = true;
					}
					break;
				case Keys::Down:
					if (gameManager->GetVisibleScreen() == GAME)
					{
						gameManager->Movement(S);
						move = true;
					}
					break;
				case Keys::Left:
					if (gameManager->GetVisibleScreen() == GAME)
					{
						gameManager->Movement(W);
						move = true;
					}
					break;
				case Keys::Right:
					if (gameManager->GetVisibleScreen() == GAME)
					{
						gameManager->Movement(E);
						move = true;
					}
					break;

					//screen keys
				case Keys::Enter:
					if (gameManager->GetVisibleScreen() == MENU || gameManager->GetVisibleScreen() == GAME)
					{
						if (!timer1->Enabled)
						{
							timer1->Enabled = true;
							bufferGraphics->FillRectangle(Brushes::Black, 0, 0, Width, Height);
							gameManager->ScreenChange(GAME);
							startCanvas->DrawImage(bufferImage, 0, 0);
						}
						else
						{
							timer1->Enabled = false;
							bufferGraphics->FillRectangle(Brushes::Black, 0, 0, Width, Height);
							gameManager->ScreenChange(MENU);
							startCanvas->DrawImage(bufferImage, 0, 0);
						}
					}
					break;

				case Keys::W:
					break;

				case Keys::E:
					if (gameManager->GetVisibleScreen() == STATUS)
					{
						timer1->Enabled = !timer1->Enabled;
					}
					break;

					//screen keys
				case Keys::R:
					if (gameManager->GetVisibleScreen() == GAME)
					{
						timer1->Enabled = !timer1->Enabled;
						bufferGraphics->FillRectangle(Brushes::Black, 0, 0, Width, Height);
						gameManager->ScreenChange(STATUS);
						startCanvas->DrawImage(bufferImage, 0, 0);
					}
					
					
					break;

				case Keys::Space:

					if (gameManager->GetVisibleScreen() == GAME || gameManager->GetVisibleScreen() == PAUSE)
					{
						timer1->Enabled = !timer1->Enabled;
						gameManager->ScreenChange(PAUSE);
						startCanvas->DrawImage(bufferImage, 0, 0);
					}

					break;

				default:
					startCanvas->DrawImage(bufferImage, 0, 0);
					break;
				}


			if (move) {
				gameManager->SpriteMove();
				gameManager->RunGame();
			}

			startCanvas->DrawImage(bufferImage, 0, 0);

		}else{ 
			if (e->KeyData == Keys::Q) {
				if (gameManager->GetVisibleScreen() == END)
				{
					Application::Restart();
				}
			}
		}
	}


	// Everytime a new game starts tell the Game manager to start and build everything.
	// also tell it that it needs to let the screen manager know that it should run the start screen.
private: System::Void MyForm_Shown(System::Object^ sender, System::EventArgs^ e) {
	bufferGraphics->FillRectangle(Brushes::Black, 0, 0, Width, Height);
	gameManager->StartGame();
	gameManager->LoadWorldMap();
	bufferGraphics->FillRectangle(Brushes::Black, 0, 0, Width, Height);
	gameManager->ScreenChange(MENU);
	startCanvas->DrawImage(bufferImage, 0, 0);
}


};
}
