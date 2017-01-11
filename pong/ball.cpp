#include "ball.hpp"
#include "game.hpp"

#define LEFT false
#define RIGHT true

void Ball::move()
{
	if (y <= 1)
	{
		dy = abs(dy);
		sound.tone(WALL_FREQ, WALL_DUR);
	}
	else if (y >= HEIGHT - BALL_SIZE - 1)
	{
		dy = -abs(dy);
		sound.tone(WALL_FREQ, WALL_DUR);
	}
	bounceOff(player, LEFT);
	bounceOff(computer, RIGHT);
	x += dx;
	y += dy;
	// paddles move but walls don't,
	// so we need to check for paddle collisions again
	bounceOff(player, LEFT);
	bounceOff(computer, RIGHT);
}

void Ball::draw() const
{
	arduboy.fillRect(x, y, BALL_SIZE, BALL_SIZE, WHITE);\
}

void Ball::bounceOff(const PaddleBase& paddle, bool side)
{
	// get the minkowski difference between the paddle and the ball
	// a-b=c, where a=paddle, b=ball, c=diff
	int16_t cx{ paddle.x - x - BALL_SIZE };
	int16_t cy{ paddle.y - y - BALL_SIZE };
	constexpr int16_t cw{ PADDLE_WIDTH + BALL_SIZE };
	constexpr int16_t ch{ PADDLE_HEIGHT + BALL_SIZE };
	// if the difference contains the origin, then a collision occured
	if (cx <= 0 && cx + cw >= 0 && cy <= 0 && cy + ch >= 0)
	{
		// ball collides on the right
		if (cx + cw == 0)
		{
			bounceOff(LEFT);
			sound.tone(PADDLE_FREQ, PADDLE_DUR);
		}
		// ball collides on the left
		else if (cx == 0)
		{
			bounceOff(RIGHT);
			sound.tone(PADDLE_FREQ, PADDLE_DUR);
		}
		// ball collides on the bottom
		else if (cy + ch == 0)
		{
			bounceOff(side);
			dy = abs(dy);
			sound.tone(PADDLE_FREQ, PADDLE_DUR);
		}
		// ball collides on the top
		else if (cy == 0)
		{
			bounceOff(side);
			dy = -abs(dy);
			sound.tone(PADDLE_FREQ, PADDLE_DUR);
		}
	}
}

void Ball::bounceOff(bool side)
{
	if (!side) // left
	{
		dx = abs(dx);
	}
	else // right
	{
		dx = -abs(dx);
	}
}
