#include "View.hpp"

View::View(Rect2D rect)
: rect(rect)
{
	SetPosition(rect.pos);
}

Vector2D View::GetPosition()
{
	return rect.pos;
}

Rect2D View::GetRect()
{
	return rect;
}

int View::GetWidth()
{
	return rect.w;
}

int View::GetHeight()
{
	return rect.h;
}

void View::SetPosition(Vector2D newPos)
{
	rect.pos.x = -newPos.x + rect.w / 2;
	rect.pos.y = -newPos.y + rect.h / 2;
}
