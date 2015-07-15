#pragma once

#include "Vector2D.hpp"
#include "Physics.hpp"

#include <vector>

class Renderer;

class Bullet {
public:
	Physics *physics;
	int lifetime;

public:
	Bullet(Vector2D pos, Vector2D vel);
	~Bullet();

	void Update();
	void Render(Renderer &ren);

	bool IsAlive();
};
