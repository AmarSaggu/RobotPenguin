#include "Object.hpp"

#include "Keyboard.hpp"
#include "Renderer.hpp"

#include <algorithm>
#include <cmath>

static int sign(int x)
{
	return (x > 0) - (x < 0);
}

Object::Object(Vector2D pos, Vector2D size)
: pos(pos), vel{0, 0}, acc{0, 0}, size(size)
{
	lag = pos;
}

Object::~Object()
{}

void Object::Input(Keyboard &key)
{
	acc.x = 0;
	acc.y = 1; // Gravity
	
	if (key.IsDown("a")) {
		acc.x -= 1;
	}
	if (key.IsDown("d")) {
		acc.x += 1;
	}
	
	// Simulate drag
	if (acc.x == 0) {
		vel.x -= sign(vel.x);
	}
	
	// Jump if on the ground
	if (vel.y == 0 && key.IsDown("w")) {
		acc.y = -20;
	}
}

void Object::Update()
{
	vel += acc;

	//size.x = 16 + std::abs(vel.x);
	//size.y = 16;

	// Limit position to bottom 
	if (pos.y + size.y + vel.y > 400) {
		vel.y = 400 - (pos.y + size.y / 2);
	}
	
	// Update position
	pos += vel;
	
	lag.x -= (lag.x - pos.x) / 2;
	lag.y -= (lag.y - pos.y) / 2;
}

void Object::Render(Renderer &ren)
{
	
	ren.SetColour(0, 0, 0);
	Vector2D floop = size;
	
	
	floop.x += std::abs(vel.x) - std::abs(vel.y);
	floop.y += std::abs(vel.y) - std::abs(vel.x);
	
	floop.x = std::min(24, floop.x);
	floop.x = std::max(8, floop.x);
	floop.y = std::min(24, floop.y);
	floop.y = std::max(8, floop.y);
	
	//ren.FillRect(pos, size);
	//ren.FillRect(lag, size);
	
	ren.SetColour(255, 204, 0);
	ren.FillRect(pos, floop);
	
	ren.SetColour(0, 0, 0);
	ren.DrawRect(pos, floop);
}
