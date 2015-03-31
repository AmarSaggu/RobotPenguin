#pragma once

struct Vector2D {
	int x, y;
	
	Vector2D();
	Vector2D(int x, int y);
	

	bool operator==(const Vector2D &vec);
	bool operator!=(const Vector2D &vec);
	void operator+=(const Vector2D &vec);
	void operator-=(const Vector2D &vec);
};
