#include "ball.hpp"
#include "game.hpp"
#include "paddle.hpp"

#define LEFT false
#define RIGHT true

const Vector& Ball::getPosition() const noexcept
{
	return position;
}

const Vector& Ball::getVelocity() const noexcept
{
	return velocity;
}

void Ball::setPosition(const Vector& v) noexcept
{
	position = v;
}

void Ball::setVelocity(const Vector& v) noexcept
{
	velocity = v;
}

void Ball::move()
{
	if (position.getY() <= 1)
	{
		velocity.setY(abs(velocity.getY()));
		sound.tone(WALL_FREQ, WALL_DUR);
	}
	else if (position.getY() >= HEIGHT - BALL_SIZE - 1)
	{
		velocity.setY(-abs(velocity.getY()));
		sound.tone(WALL_FREQ, WALL_DUR);
	}
	bounceOff(player, LEFT);
	bounceOff(computer, RIGHT);
	position.setX(position.getX() + velocity.getX());
	position.setY(position.getY() + velocity.getY());
	// paddles move but walls don't,
	// so we need to check for paddle collisions again
	bounceOff(player, LEFT);
	bounceOff(computer, RIGHT);
}

void Ball::draw() const
{
	arduboy.fillRect(position.getX(), position.getY(), BALL_SIZE,
		BALL_SIZE, WHITE);
}

void Ball::bounceOff(const PaddleBase& paddle, bool side)
{
	// get the minkowski difference between the paddle and the ball
	// a-b=c, where a=paddle, b=ball, c=diff
	int16_t cx{ paddle.getPosition().getX() - position.getX() - BALL_SIZE };
	int16_t cy{ paddle.getPosition().getY() - position.getY() - BALL_SIZE };
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
			velocity.setY(abs(velocity.getY()));
			sound.tone(PADDLE_FREQ, PADDLE_DUR);
		}
		// ball collides on the top
		else if (cy == 0)
		{
			bounceOff(side);
			velocity.setY(-abs(velocity.getY()));
			sound.tone(PADDLE_FREQ, PADDLE_DUR);
		}
	}
}

void Ball::bounceOff(bool side)
{
	if (!side) // left
	{
		velocity.setX(abs(velocity.getX()));
	}
	else // right
	{
		velocity.setX(-abs(velocity.getX()));
	}
}
