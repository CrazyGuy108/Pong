#ifndef BALL_HPP
#define BALL_HPP

#include <stdint.h>
#include "paddle.hpp"

#define BALL_SIZE 3

class Ball
{
public:
	// moves and bounces the ball based on dx and dy
	void move();

	// draws the ball on the screen
	void draw() const;

	int16_t x;
	int16_t y;
	int16_t dx;
	int16_t dy;

private:
	// verifies and responds to a collision with a paddle
	// on the ball's left(false) or right(true) side
	void bounceOff(const PaddleBase& paddle, bool side);

	// bounces the ball off of the left(false) or right(true) side
	void bounceOff(bool side);
};

#endif // BALL_HPP
