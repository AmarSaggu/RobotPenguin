#include "Keyboard.hpp"

#include <SDL2/SDL.h>

#include <cassert>

Keyboard::Keyboard()
{
	keyboard = SDL_GetKeyboardState(nullptr); 
}

bool Keyboard::IsDown(const char *name) const
{
	SDL_Scancode scancode = SDL_GetScancodeFromName(name);

	assert(scancode != SDL_SCANCODE_UNKNOWN);
	return keyboard[scancode];
}
