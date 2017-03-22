#ifndef BALL_HPP
#define BALL_HPP

#include "vector.hpp"
#include <stdint.h>

#define BALL_SIZE 3

class PaddleBase;

class Ball
{
public:
	const Vector& getPosition() const noexcept;
	const Vector& getVelocity() const noexcept;
	void setPosition(const Vector& v) noexcept;
	void setVelocity(const Vector& v) noexcept;

	// moves and bounces the ball based on dx and dy
	void move();

	// draws the ball on the screen
	void draw() const;

private:
	// verifies and responds to a collision with a paddle
	// on the ball's left(false) or right(true) side
	void bounceOff(const PaddleBase& paddle, bool side);

	// bounces the ball off of the left(false) or right(true) side
	void bounceOff(bool side);

	Vector position;
	Vector velocity;
};

#endif // BALL_HPP
