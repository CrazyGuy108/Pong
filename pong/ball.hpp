#ifndef BALL_HPP
#define BALL_HPP

#include <stdint.h>

#define BALL_SIZE 3

class Ball
{
public:
	// moves the ball based on dx and dy
	void move();

	// bounces the ball off the paddles and walls
	void bounce();

	// draws the ball on the screen
	void draw() const;

	int16_t x;
	int16_t y;
	int16_t dx;
	int16_t dy;
};

#endif // BALL_HPP
