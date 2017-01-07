#ifndef GAME_HPP
#define GAME_HPP

#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "ball.hpp"
#include "paddle.hpp"

#define WALL_FREQ   NOTE_A3
#define PADDLE_FREQ NOTE_A4
#define POINT_FREQ  NOTE_B4
#define WALL_DUR    16
#define PADDLE_DUR  96
#define POINT_DUR   257

extern Arduboy2 arduboy; // found in pong.ino
extern ArduboyTones sound; // found in pong.ino

extern void (*gameTick)();
extern Ball ball;
extern Player player;
extern Computer computer;

#endif // GAME_HPP
