#pragma once

#include "Vector2D.hpp"
#include <cstdint>

class Mouse {
	std::uint32_t state;
	Vector2D pos;
	
public:
	enum MouseButton {
		LEFT,
		MIDDLE,
		RIGHT
	};
	
	void Update();
	
	Vector2D GetPosition() const;
	bool IsDown(MouseButton button) const;
};
