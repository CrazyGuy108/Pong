#include "ball.hpp"
#include "game.hpp"

void Ball::move()
{
	x += dx;
	y += dy;
}

void Ball::bounce()
{
	// bounce off the two paddles
	if ((ball.x == player.x + PADDLE_WIDTH &&
			ball.y + BALL_SIZE > player.y &&
			ball.y < player.y + PADDLE_HEIGHT) ||
		(ball.x + BALL_SIZE == computer.x &&
			ball.y + BALL_SIZE > computer.y &&
			ball.y < computer.y + PADDLE_HEIGHT))
	{
		ball.dx = -ball.dx;
		sound.tone(PADDLE_FREQ, PADDLE_DUR);
	}
	// bounce off the top and bottom of the screen
	if (ball.y <= 1 || ball.y >= HEIGHT - BALL_SIZE - 1)
	{
		ball.dy = -ball.dy;
		sound.tone(WALL_FREQ, WALL_DUR);
	}
}

void Ball::draw() const
{
	arduboy.fillRect(x, y, BALL_SIZE, BALL_SIZE, WHITE);
}
