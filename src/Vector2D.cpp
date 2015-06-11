#include "Vector2D.hpp"

#include <cmath>

Vector2D::Vector2D()
: x(0), y(0)
{}

Vector2D::Vector2D(double x, double y)
: x(x), y(y)
{}

double Vector2D::GetLength() const
{
	return std::sqrt(x*x + y*y);
}

double Vector2D::GetDistance(const Vector2D &vec) const
{
	return sqrt(pow(x-vec.x, 2.0) + pow(y-vec.y, 2.0));
}

bool Vector2D::operator==(const Vector2D &vec)
{
	return (x == vec.x && y == vec.y);
}
bool Vector2D::operator!=(const Vector2D &vec)
{
	return !operator==(vec);
}

void Vector2D::operator+=(const Vector2D &vec)
{
	x += vec.x;
	y += vec.y;
}
void Vector2D::operator-=(const Vector2D &vec)
{
	x -= vec.x;
	y -= vec.y;
}

void Vector2D::operator*=(double f)
{
	x *= f;
	y *= f;
}
void Vector2D::operator/=(double f)
{
	x /= f;
	y /= f;
}

Vector2D Vector2D::operator+(const Vector2D &vec)
{
	return {x + vec.x, y + vec.y};
}
Vector2D Vector2D::operator-(const Vector2D &vec)
{
	return {x - vec.x, y - vec.y};
}

Vector2D Vector2D::operator*(double f)
{
	return {x * f, y * f};
}
Vector2D Vector2D::operator/(double f)
{
	return {x / f, y / f};
}
