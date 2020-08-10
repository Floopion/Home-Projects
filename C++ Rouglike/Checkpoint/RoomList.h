/*
  Program name:        Pikachu Rougelike
  Project file name:   RoomList.h
  Date:                15/05/2020
  Language:            C++
  Platform:			   Microsoft Visual Studio 2017 - 2019
  Purpose:			   To keep track of each room and how many there are.
  Description:         This class holds a list off all the rooms. It can retun the number of a specific room,
					   and which room to enter.
  Known Bugs:          -
*/
#pragma once
#include "Room.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class RoomList
{
private:
	//array of rooms
	array<Room^>^ roomArray;
	//number of rooms
	int nRooms;

public:
	RoomList(int startNRoom);
	//method to add rooms
	void SetRoomArrayEntry(int roomIndex, Room^ roomToEnter);
	Room^ GetRoom(int roomIndex);
};

