#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "vector.hpp"
#include <stdint.h>

#define PADDLE_WIDTH 4
#define PADDLE_HEIGHT 12

// base paddle class
class PaddleBase
{
public:
	const Vector& getPosition() const noexcept;
	void setPosition(const Vector& v) noexcept;

	// draws the paddle on the screen
	void draw() const;

	int8_t score;

protected:
	PaddleBase() = default;

	// moves the paddle up(-) or down(+)
	void move(int16_t distance);

private:
	Vector position;
};

// statically polymorphic paddle
template<typename T>
class Paddle
	: public PaddleBase
{
public:
	void move();

protected:
	Paddle() = default;
};

// player paddle
class Player final
	: public Paddle<Player>
{
	friend class Paddle<Player>;
private:
	void move_impl();
};

// computer paddle
class Computer final
	: public Paddle<Computer>
{
	friend class Paddle<Computer>;
private:
	void move_impl();
};

template<typename T>
void Paddle<T>::move()
{
	static_cast<T*>(this)->move_impl();
}

#endif // PADDLE_HPP
