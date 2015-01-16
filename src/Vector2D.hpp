#pragma once

struct Vector2D {
	int x, y;
	
	Vector2D();
	Vector2D(int x, int y);
	
	void operator+=(const Vector2D &vec);
};
