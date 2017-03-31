#include "game.hpp"
#include "vector.hpp"

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

typedef void (*tick_func_t)();

static tick_func_t gameTick{ &menuTitle };

Ball ball;
Player player;
Computer computer;

void tick()
{
	gameTick();
}

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
	arduboy.print(player.getScore());
	arduboy.setCursor(WIDTH/2 + 3, 2);
	arduboy.print(computer.getScore());
	// objects
	ball.draw();
	player.draw();
	computer.draw();
}

void
resetBall()
{
	ball.setPosition(Vector{ WIDTH / 2, HEIGHT / 2 });
	ball.setVelocity(Vector{ 1, 1 });
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
	// i thought of something funnier than 24...
	player.setPosition(Vector{ 9, 24 });
	player.resetScore();
	computer.setPosition(Vector{ WIDTH - PADDLE_WIDTH - 9, 25 });
	computer.resetScore();
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
	if (ball.getPosition().getX() >= WIDTH - BALL_SIZE)
	{
		player.updateScore();
		if (player.getScore() >= SCORE_MAX)
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
	else if (ball.getPosition().getX() < 1)
	{
		computer.updateScore();
		if (computer.getScore() >= SCORE_MAX)
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
