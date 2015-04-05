#include "Player.hpp"
#include "Keyboard.hpp"
#include "LineSkip.hpp"
#include "View.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include <cmath>

#include <cstdlib>

Player::Player(Vector2D pos)
: Object({pos, 16, 16})
{}

void Player::Input(Keyboard &key)
{
	acc.x = 0;
	acc.y = 1;

	if (key.IsDown("a")) {
		acc.x--;
	}
	if (key.IsDown("d")) {
		acc.x++;
	}
	/*if (key.IsDown("w")) {
		acc.y--;
	} 
	if (key.IsDown("s")) {
		acc.y++;
	}*/

	if (key.IsDown("w") && vel.y >= 0) {
		acc.y = -20;
	}
}
