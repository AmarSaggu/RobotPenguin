#include "View.hpp"

View::View(Vector2D pos, int width, int height)
: width(width), height(height)
{
	SetPosition(pos);
}

Vector2D View::GetPosition()
{
	return pos;
}

int View::GetWidth()
{
	return width;
}

int View::GetHeight()
{
	return height;
}

void View::SetPosition(Vector2D newPos)
{
	pos.x = -newPos.x + width / 2;
	pos.y = -newPos.y + height / 2;
}
