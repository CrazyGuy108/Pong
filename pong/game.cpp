#include "game.hpp"

#define SCORE_MAX 3

// helper functions

static void
draw();

static void
resetBall();

// game state functions

static void
menuTitle();

static void
gameSetup();

static void
gameMain();

static void
gamePause();

static void
menuWin();

static void
menuLose();

void (*gameTick)(){ &menuTitle };
Ball ball;
Player player;
Computer computer;

void
draw()
{
	// cool border around the screen
	arduboy.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
	// dotted line in the middle
	for (uint8_t i{ 2 }; i < HEIGHT; i += 8)
	{
		arduboy.drawFastVLine(WIDTH / 2, i, 4, WHITE);
	}
	// scores
	arduboy.setCursor(WIDTH/2 - 12, 2);
	arduboy.print(player.score);
	arduboy.setCursor(WIDTH/2 + 3, 2);
	arduboy.print(computer.score);
	// objects
	ball.draw();
	player.draw();
	computer.draw();
}

void
resetBall()
{
	ball.x = WIDTH / 2;
	ball.y = HEIGHT / 2;
	ball.dx = 1;
	ball.dy = 1;
}

void
menuTitle()
{
	arduboy.setCursor(0, 0);
	arduboy.print(F("Press A to\nstart"));
	if (arduboy.justPressed(A_BUTTON))
	{
		gameTick = &gameSetup;
	}
}

void
gameSetup()
{
	arduboy.initRandomSeed();
	resetBall();
	player.x = 9;
	player.y = 24; // i thought of something funnier than 24...
	player.score = 0;
	computer.x = WIDTH - PADDLE_WIDTH - 9;
	computer.y = 25; // twenyfiiive!
	computer.score = 0;
	draw();
	arduboy.display();
	delay(1000);
	gameTick = &gameMain;
}

void
gameMain()
{
	draw();
	// pause the game if needed
	if (arduboy.justPressed(A_BUTTON))
	{
		gameTick = &gamePause;
		return;
	}
	ball.move();
	// check if someone scored
	if (ball.x >= WIDTH - BALL_SIZE)
	{
		sound.tone(POINT_FREQ, POINT_DUR);
		if (++player.score >= SCORE_MAX)
		{
			gameTick = &menuWin;
			return;
		}
		else
		{
			resetBall();
		}
	}
	else if (ball.x < 1)
	{
		sound.tone(POINT_FREQ, POINT_DUR);
		if (++computer.score >= SCORE_MAX)
		{
			gameTick = &menuLose;
			return;
		}
		else
		{
			resetBall();
		}
	}
	ball.bounce();
	player.move();
	computer.move();
}

void
gamePause()
{
	draw();
	// resume the game if needed
	if (arduboy.justPressed(A_BUTTON))
	{
		gameTick = &gameMain;
	}
}

void
menuWin()
{
	arduboy.setCursor(0, 0);
	arduboy.print(F("You win!\nPress A to\nrestart"));
	if (arduboy.justPressed(A_BUTTON))
	{
		gameTick = &gameSetup;
	}
}

void
menuLose()
{
	arduboy.setCursor(0, 0);
	arduboy.print(F("You lost!\nPress A to\nrestart"));
	if (arduboy.justPressed(A_BUTTON))
	{
		gameTick = &gameSetup;
	}
}
