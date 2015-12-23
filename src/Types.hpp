#pragma once

#include <cstddef>

using Id = size_t;

struct Vec {
	double x, y;
	
public:
	bool operator==(const Vec v);
	bool operator!=(const Vec v);

	void operator+=(const Vec v);
	void operator-=(const Vec v);

	void operator*=(double s);
	void operator/=(double s);

	Vec operator+(const Vec v);
	Vec operator-(const Vec v);

	Vec operator*(double s);
	Vec operator/(double s);
};

struct Box {
	Vec pos, size;
};
