#pragma once

#include "Vector2D.hpp"

class View {
public:
	View(Vector2D pos, int width, int height);
	
	Vector2D GetPosition();
	
	int GetWidth();
	int GetHeight();

		
	void SetPosition(Vector2D newPos);
private:
	Vector2D pos;
	int width, height;
};
