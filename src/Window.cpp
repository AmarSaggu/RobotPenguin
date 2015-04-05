#include "Window.hpp"

#include <SDL2/SDL.h>

Window::Window()
: win(nullptr), size{0, 0}
{}

Window::~Window()
{
	Destroy();
}

bool Window::Create(int width, int height, bool fullscreen /* = false*/)
{
	int x = SDL_WINDOWPOS_CENTERED;
	int y = SDL_WINDOWPOS_CENTERED;
	int flags = 0;
	
	if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	
	win = SDL_CreateWindow("Bloop!", x, y, width, height, flags);
	//assert(win);
	
	// Update window size information
	SDL_GetWindowSize(win, &size.x, &size.y);
	
	return win;
}

void Window::Destroy()
{	
	if (win) {
		SDL_DestroyWindow(win);
		win = nullptr;
	}
}

Vector2D Window::GetSize()
{
	return size;
}

SDL_Window *Window::GetHandle()
{
	return win;
}
