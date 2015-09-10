#pragma once

#include "Bullet.hpp"

#include "Vector2D.hpp"

#include <vector>

class Physics;
class Controller;
class Renderable;

class Player {
	Physics *physics;
	Controller *controller;
	Renderable *renderable;

	std::vector<Bullet> bullets;

public:
	Player(Physics *p, Controller *c, Renderable *r);
};
