/*
  Program name:        Rougelike
  Project file name:   Item List
  Date:                15/05/2020
  Language:            C++
  Platform:				Microsoft Visual Studio 2017 - 2019
  Purpose:				Holds Linked List of Items
  Description:			Methods to add, delete, draw, set position, and count items
  Known Bugs:			Nothing currently
*/

#pragma once
#include "Item.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class ItemList
{
private:
	Item^ head;
	Item^ tail;

public:
	ItemList(void);

	void AddItem(Item^ newItem);
	void DeleteItem(Item^ itemToDelete);
	void DeleteAllItem();
	void DrawItemInViewport(int xViewport, int yViewport);
	void SetItemLocation(int roomIndex);

	Point ItemPosition(int itemToFind);
	int ItemCount();
	void KillSingleItem(int itemToKill);
	void DeleteDeadItems();
};