#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

ref class test
{
private:
	Random^ rGen;

public:
	property int xTile;
	property int yTile;
	property int tileWidth;
	property int tileHeight;

	test(Random^ startRGen);
};
