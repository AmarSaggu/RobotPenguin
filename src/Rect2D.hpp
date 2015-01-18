#pragma once

#include "Vector2D.hpp"

struct Rect2D {
	Vector2D pos;
	int w, h;
	
	Vector2D GetDistance(struct Rect2D b);
};
