#include "View.hpp"

View::View(int x, int y, int width, int height)
: x(x), y(y), width(width), height(height)
{
	//
}

int View::GetPositionX()
{
	return x;
}

int View::GetPositionY()
{
	return y;
}

int View::GetWidth()
{
	return width;
}

int View::GetHeight()
{
	return height;
}

void View::SetPosition(int x, int y)
{
	this->x = -x + width / 2;
	this->y = -y + height / 2;
}


