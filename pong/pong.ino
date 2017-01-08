#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "game.hpp"

Arduboy2 arduboy;
ArduboyTones sound{ arduboy.audio.enabled };

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
	arduboy.pollButtons();
	gameTick();
	arduboy.display(CLEAR_BUFFER);
}
