#include "Rect2D.hpp"

#include <cmath>

Vector2D Rect2D::GetDistance(Rect2D b)
{
	Vector2D dist;
	dist.x = std::round(std::abs((pos.x + w / 2.0) - (b.pos.x + b.w / 2.0)) - w / 2.0 - b.w / 2.0);
	dist.y = std::round(std::abs((pos.y + h / 2.0) - (b.pos.y + b.h / 2.0)) - h / 2.0 - b.h / 2.0);
	
	return dist;
}
