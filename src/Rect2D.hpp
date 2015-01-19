#pragma once

#include "Vector2D.hpp"

struct Rect2D {
	Vector2D pos;
	int w, h;
	
	bool Contains(Vector2D point);
	bool Intersects(Rect2D b);
	
	Vector2D GetDistance(Rect2D b);
};
