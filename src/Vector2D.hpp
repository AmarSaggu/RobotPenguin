#pragma once

struct Vector2D {
	double x, y;
	
	Vector2D();
	Vector2D(double x, double y);

	double GetLength() const;
	
	double GetDistance(const Vector2D &vec) const;

	bool operator==(const Vector2D &vec);
	bool operator!=(const Vector2D &vec);
	void operator+=(const Vector2D &vec);
	void operator-=(const Vector2D &vec);
	
	void operator*=(double f);
	void operator/=(double f);
	
	Vector2D operator+(const Vector2D &vec);
	Vector2D operator-(const Vector2D &vec);
	
	Vector2D operator*(double f);
	Vector2D operator/(double f);
};
