#pragma once

#include "Rect2D.hpp"

class View {
public:
	View(Rect2D rect);
	
	Vector2D GetPosition();
	Rect2D GetRect();
	
	int GetWidth();
	int GetHeight();

	void SetPosition(Vector2D newPos);
private:
	Rect2D rect;
};
