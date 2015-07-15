#include "Mouse.hpp"

#include <SDL2/SDL.h>

void Mouse::Update()
{
	int posX, posY;
	state = SDL_GetMouseState(&posX, &posY);
	
	pos.x = posX;
	pos.y = posY;
}

Vector2D Mouse::GetPosition()
{
	return pos;
}

bool Mouse::IsDown(MouseButton button)
{
	int pressed = 0;
	
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
