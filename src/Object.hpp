#pragma once

#include "Vector2D.hpp"

class Keyboard;
class Renderer;

/*
A solid object that collides with the worlds geometry
*/
class Object {
	Vector2D pos, vel, acc;
	Vector2D size;
	
public:
	Object(Vector2D pos, Vector2D size);
	virtual ~Object();
	
	virtual void Input(Keyboard &key);
	virtual void Update();
	virtual void Render(Renderer &ren);
};
