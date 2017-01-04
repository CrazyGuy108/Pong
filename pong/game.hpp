#ifndef GAME_HPP
#define GAME_HPP

#include <Arduboy2.h>
#include "ball.hpp"
#include "paddle.hpp"

extern Arduboy2 arduboy; // found in pong.ino

extern void (*gameTick)();
extern Ball ball;
extern Player player;
extern Computer computer;

#endif // GAME_HPP
