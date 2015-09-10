#pragma once

#include "Vector2D.hpp"
#include "Rect2D.hpp"

struct Physics {
	Rect2D box;
	Vector2D vel, acc;

	bool onGround;
	
public:
	Physics(Rect2D box);
	
	void ApplyImpulse(Vector2D impulse);
	void Update();
};
