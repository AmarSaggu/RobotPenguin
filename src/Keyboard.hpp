#pragma once

#include <cstdint>

class Keyboard {
	const std::uint8_t *keyboard;

public:
	Keyboard();
	
	bool IsDown(const char *name) const;
	bool IsDown(int scancode);
};
