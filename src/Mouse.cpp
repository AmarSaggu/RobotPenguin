#include "Mouse.hpp"

#include <SDL2/SDL.h>

void Mouse::Update()
{
	state = SDL_GetMouseState(&pos.x, &pos.y);
}

Vector2D Mouse::GetPosition() const
{
	return pos;
}

bool Mouse::IsDown(MouseButton button) const
{
	int pressed;
	
	switch (button) {
	case LEFT:
		pressed = SDL_BUTTON_LEFT;
		break;
	
	case MIDDLE:
		pressed = SDL_BUTTON_MIDDLE;
		break;
	
	case RIGHT:
		pressed = SDL_BUTTON_RIGHT;
		break;
	}

	return state & SDL_BUTTON(pressed);
}
