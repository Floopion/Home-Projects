#include "test.h"

test::test(Random^ startRGen)
{
	rGen = startRGen;
	xTile = rGen->Next(59);
	yTile = rGen->Next(31);
	tileWidth = rGen->Next(3, 10);
	tileHeight = rGen->Next(3, 10);
}