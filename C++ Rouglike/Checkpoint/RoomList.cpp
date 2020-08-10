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

#include "RoomList.h"

RoomList::RoomList(int startNRoom)
{
	nRooms = startNRoom;
	roomArray = gcnew array<Room^>(nRooms);
}

void RoomList::SetRoomArrayEntry(int roomIndex, Room^ roomToEnter)
{
	roomArray[roomIndex] = roomToEnter;
}

Room^ RoomList::GetRoom(int roomIndex)
{
	return roomArray[roomIndex];
}
