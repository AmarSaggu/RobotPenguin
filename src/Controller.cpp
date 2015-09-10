#include "Controller.hpp"
#include "Physics.hpp"
#include "Keyboard.hpp"
#include "Utils.hpp"

#include <SDL2/SDL.h>

Controller::Controller(Physics &physics, Keyboard &key)
: physics(physics), key(key)
{
	left = SDL_SCANCODE_A;
	right = SDL_SCANCODE_D;
	jump = SDL_SCANCODE_W;
}

void Controller::Update()
{
	if (key.IsDown(left)) {
		physics.ApplyImpulse({-1.0, 0.0});
	}
	if (key.IsDown(right)) {
		physics.ApplyImpulse({1.0, 0.0});
	}
	
	// Apply drag
	if (physics.acc.x == 0.0) {
		physics.ApplyImpulse({-sign(physics.vel.x), 0.0});
	}
	
	// Jump!
	if (physics.onGround && key.IsDown(jump) && physics.vel.y == 0.0) {
		physics.ApplyImpulse({0.0, -15.0});
	}
	
	// Simulate gravity
	physics.ApplyImpulse({0.0, 1.0});
}

void Controller::ArrowKeys()
{
	left = SDL_SCANCODE_LEFT;
	right = SDL_SCANCODE_RIGHT;
	jump = SDL_SCANCODE_UP;
}
