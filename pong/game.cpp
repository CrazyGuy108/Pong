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
	ball.position.setX(WIDTH / 2);
	ball.position.setY(HEIGHT / 2);
	ball.velocity.setX(1);
	ball.velocity.setY(1);
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
	player.position.setX(9);
	player.position.setY(24); // i thought of something funnier than 24...
	player.score = 0;
	computer.position.setX(WIDTH - PADDLE_WIDTH - 9);
	computer.position.setY(25); // twenyfiiive!
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
	player.move();
	computer.move();
	// check if the player scored
	if (ball.position.getX() >= WIDTH - BALL_SIZE)
	{
		if (++player.score >= SCORE_MAX)
		{
			gameTick = &menuWin;
		}
		else
		{
			resetBall();
		}
		sound.tone(POINT_FREQ, POINT_DUR);
	}
	// check if the computer scored
	else if (ball.position.getX() < 1)
	{
		if (++computer.score >= SCORE_MAX)
		{
			gameTick = &menuLose;
		}
		else
		{
			resetBall();
		}
		sound.tone(POINT_FREQ, POINT_DUR);
	}
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
