#pragma once

#include "Vector2D.hpp"



class LineArray;
class View;

struct SDL_Renderer;

/*
A solid object that collides with the worlds geometry.
*/
class Object {
public:
	Object(Vector2D pos);
	virtual ~Object();

	void HandleWorldCollision(LineArray &world);

	virtual void Logic(LineArray &world);
	virtual void Render(SDL_Renderer *ren, View &view);

private:
	Vector2D pos, vel, acc;
	int width, height;
};
