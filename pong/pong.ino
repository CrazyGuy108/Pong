#include <Arduboy2.h>
#include "game.hpp"

Arduboy2 arduboy;

void
setup()
{
	arduboy.begin();
	arduboy.setFrameRate(30);
	arduboy.setTextSize(2);
	arduboy.clear();
}

void
loop()
{
	if (!arduboy.nextFrame())
	{
		return;
	}
	gameTick();
	arduboy.display(CLEAR_BUFFER);
}
