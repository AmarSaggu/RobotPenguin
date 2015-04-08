#include "Object.hpp"

#include "Keyboard.hpp"
#include "Renderer.hpp"

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

	// Limit position to bottom 
	if (pos.y + size.y + vel.y > 400) {
		vel.y = 400 - (pos.y + size.y / 2);
	}
	
	// Update position
	pos += vel;
}

void Object::Render(Renderer &ren)
{
	ren.DrawRect(pos, size);
}
