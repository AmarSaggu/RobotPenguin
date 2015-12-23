#pragma once

#include "Types.hpp"

#include <cstdint>

class Mouse {
	uint32_t state;
	Vec pos;
	
public:
	enum class MouseButton {
		LEFT,
		MIDDLE,
		RIGHT
	};
	
	void Update();
	
	Vec GetPosition() const;
	bool IsDown(MouseButton button) const;
};
