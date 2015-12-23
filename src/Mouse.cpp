#include "Mouse.hpp"

#include <SDL2/SDL.h>

void Mouse::Update()
{
	int x, y;
	state = SDL_GetMouseState(&x, &y);
	
	pos.x = x;
	pos.y = y;
}

Vec Mouse::GetPosition() const
{
	return pos;
}

bool Mouse::IsDown(MouseButton button) const
{
	int pressed = 0;
	
	switch (button) {
	case MouseButton::LEFT:
		pressed = SDL_BUTTON_LEFT;
		break;
	
	case MouseButton::MIDDLE:
		pressed = SDL_BUTTON_MIDDLE;
		break;
	
	case MouseButton::RIGHT:
		pressed = SDL_BUTTON_RIGHT;
		break;
	}

	return state & SDL_BUTTON(pressed);
}
