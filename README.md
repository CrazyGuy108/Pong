# Pong v1.3.0
A Pong clone for the Arduboy

## Controls
* Up and Down buttons: Move the left paddle up or down respectively.
* A and B buttons: Move the right paddle up or down respectively (2player mode).
* Left button: Pause and unpause the game.

## Features
* Basic singleplayer mode AI that can be beat.
* Ball can travel at an angle (without floating point math!).
* Also changes its direction based on where it hits the paddle.

## Things I learned
This game taught me the basics of vector math. I was able to calculate the new velocity of the ball based on its position and the center of the paddle it was hitting. After that, a version of Bresenham's line algorithm was used to animate the ball using ints instead of floats (a huge performance gain in the context of an 8-bit Arduino microcontroller!), mostly copied from Arduboy2's implementation.

## Copyright
This project is under the MIT license.
