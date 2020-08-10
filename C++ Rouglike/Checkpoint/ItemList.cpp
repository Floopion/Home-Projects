#include "ItemList.h"

ItemList::ItemList()
{
	head = nullptr;
	tail = nullptr;
}

//adds item to the Item List
void ItemList::AddItem(Item^ newItem)
{
	if (tail == nullptr)
	{
		head = newItem;
		tail = newItem;
	}
	else
	{
		tail->Next = newItem;
		tail = newItem;
	}
}

//Delete specified Item which has been passed from the 
void ItemList::DeleteItem(Item^ itemToDelete)
{
	Item^ spriteWalker = head;
	if (spriteWalker == tail)
	{
		head = nullptr;
		tail = nullptr;
	}
	else if (itemToDelete == spriteWalker)
	{
		head = spriteWalker->Next;
	}
	else
	{
		while (spriteWalker->Next != itemToDelete)
		{
			spriteWalker = spriteWalker->Next;
		}
		spriteWalker->Next = itemToDelete->Next;
		if (itemToDelete == tail)
		{
			tail = spriteWalker;
		}
	}
}

//Deletes all items and allows reset on loading new dungeon level
void ItemList::DeleteAllItem()
{
	Item^ spriteWalker = head;

	while (spriteWalker != nullptr)
	{
		DeleteItem(spriteWalker);
		spriteWalker = spriteWalker->Next;
	}
}

//draws item on viewport
void ItemList::DrawItemInViewport(int xViewport, int yViewport)
{
	Item^ spriteWalker = head;

	while (spriteWalker != nullptr)
	{
		int newXPos = spriteWalker->xPos - xViewport;
		int newYPos = spriteWalker->yPos - yViewport;

		if (newXPos >= 0 && newYPos >= 0 && newXPos <= 100 * 32 && newYPos <= 50 * 32)
		{
			//item needs draw method
			spriteWalker->DrawPlayerViewport(newXPos, newYPos);
		}
		spriteWalker = spriteWalker->Next;
	}
}

//returns the position of the item that is specified back to the gameManager which will use this to determine collision
Point ItemList::ItemPosition(int itemToFind)
{
	Item^ spriteWalker = head;
	int indexToFind = itemToFind;
	int currentIndex = 0;

	do
	{
		if (currentIndex == indexToFind)
		{
			//returns the point position of the item specified
			return spriteWalker->GetPoint();
		}
		spriteWalker = spriteWalker->Next;
		currentIndex++;
	} while (currentIndex < indexToFind + 1);

}

// sets the item to a specific room
void ItemList::SetItemLocation(int roomIndex)
{
	Item^ spriteWalker = head;
	while (spriteWalker != nullptr)
	{
		for (int i = 1; i < roomIndex; i++)
		{

			//item needs set position method
			spriteWalker->setItemStart(i);
			spriteWalker = spriteWalker->Next;
		}

	}
}

//determines the number of items in the list
int ItemList::ItemCount()
{
	int count = 0;

	Item^ spriteWalker = head;
	while (spriteWalker != nullptr)
	{
		count++;
		spriteWalker = spriteWalker->Next;
	}
	return count;
}

//changes the isAlive boolean of the item so it can it will be deleted in the dead dead items
void ItemList::KillSingleItem(int itemToKill)
{
	Item^ spriteWalker = head;

	int indexToKill = itemToKill;
	int currentIndex = 0;
	do
	{
		if (currentIndex == indexToKill)
		{
			spriteWalker->isAlive = false;
		}
		spriteWalker = spriteWalker->Next;
		currentIndex++;
	} while (currentIndex < indexToKill + 1);
}

//deletes all items which have a isAlive boolean = false
void ItemList::DeleteDeadItems() {
	Item^ spriteWalker = head;
	while (spriteWalker != nullptr)
	{
		if (!spriteWalker->isAlive)
		{
			DeleteItem(spriteWalker);
		}
		spriteWalker = spriteWalker->Next;
	}
}