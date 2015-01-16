#include "Vector2D.hpp"

Vector2D::Vector2D()
: x(0), y(0)
{}

Vector2D::Vector2D(int x, int y)
: x(x), y(y)
{}


void Vector2D::operator+=(const Vector2D &vec)
{
	x += vec.x;
	y += vec.y;
}

