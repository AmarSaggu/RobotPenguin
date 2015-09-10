#pragma once

#include "Vector2D.hpp"
#include "Physics.hpp"
#include "Renderable.hpp"

#include <vector>

class Renderer;

class Bullet {
public:
	Physics *physics;
	Renderable *renderable;
	int lifetime;

public:
	Bullet(Vector2D pos, Vector2D vel, Renderer &ren);
	~Bullet();

	void Update();
	void Render();

	bool IsAlive();
};
