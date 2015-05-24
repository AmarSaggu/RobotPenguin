#include "Object.hpp"

#include "Keyboard.hpp"
#include "Renderer.hpp"

#include <cstdlib>
#include <algorithm>

static int sign(int x)
{
	return (x > 0) - (x < 0);
}

Object::Object(Vector2D pos, Vector2D size)
: pos(pos), vel{0, 0}, acc{0, 0}, size(size)
{}

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
	
	// Jump if on the ground
	if (vel.y == 0 && acc.y >= 0 &&  key.IsDown("w")) {
		acc.y = -20;
	}
}

void Object::Update()
{	
	// Simulate drag
	if (acc.x == 0) {
		vel.x -= sign(vel.x);
	}

	vel += acc;

	// Collide with the ground
	if (pos.y + size.y + vel.y > 900) {
		vel.y = 900 - (pos.y + size.y / 2);
	}
	
	// Update position
	pos += vel;
}

void Object::Render(Renderer &ren)
{
	ren.SetColour(0, 0, 0);
	Vector2D bounds = size;	
	
	bounds.x += std::abs(vel.x) - std::abs(vel.y);
	bounds.y += std::abs(vel.y) - std::abs(vel.x);
	
	bounds.x = std::min(size.x + size.x/2, bounds.x);
	bounds.y = std::min(size.y + size.y/2, bounds.y);
	bounds.x = std::max(size.x/2, bounds.x);
	bounds.y = std::max(size.y/2, bounds.y);
	
	ren.SetColour(255, 204, 0);
	ren.FillRect(pos, bounds);
	
	ren.SetColour(0, 0, 0);
	ren.DrawRect(pos, bounds);
}
