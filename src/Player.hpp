#pragma once

#include "Bullet.hpp"

#include "Vector2D.hpp"

#include <vector>

class Physics;
class Controller;
class Renderable;
class Keyboard;

class Player {
	Physics *physics;
	Controller *controller;
	Renderable *renderable;

	std::vector<Bullet> bullets;

public:
	Player(Vector2D pos, Keyboard &key, Renderer &ren);
	~Player();

	void Input();
	void Update();
	void Render();
};
