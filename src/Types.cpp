#include "Types.hpp"

bool Vec::operator==(const Vec v)
{
	return (x == v.x && y == v.y);
}

bool Vec::operator!=(const Vec v)
{
	return (x != v.x && y != v.y);
}

void Vec::operator+=(const Vec v)
{
	x += v.x;
	y += v.y;
}

void Vec::operator-=(const Vec v)
{
	x -= v.x;
	y -= v.y;
}

void Vec::operator*=(double s)
{
	x *= s;
	y *= s;
}

void Vec::operator/=(double s)
{
	x /= s;
	y /= s;
}

Vec Vec::operator+(const Vec v)
{
	return {x + v.x, y + v.y};
}

Vec Vec::operator-(const Vec v)
{
	return {x - v.x, y - v.y};
}

Vec Vec::operator*(double s)
{
	return {x * s, y * s};
}

Vec Vec::operator/(double s)
{
	return {x / s, y / s};
}
