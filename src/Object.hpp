#pragma once

#include "Rect2D.hpp"
#include "Vector2D.hpp"

class LineArray;
class View;
class Keyboard;

struct SDL_Renderer;

/*
A solid object that collides with the worlds geometry.
*/
class Object {
public:
	Object();
	Object(Rect2D pos);
	virtual ~Object();
	
	void Input(Keyboard &key);
	void HandleWorldCollision(LineArray &world);

	virtual void Logic(LineArray &world);
	virtual void Render(SDL_Renderer *ren, View &view);

private:
	Rect2D rect;
	Vector2D vel, acc;
};
