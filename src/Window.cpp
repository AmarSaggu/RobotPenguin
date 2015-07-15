#include "Window.hpp"

#include <SDL2/SDL.h>


Window::Window(int width, int height, bool fullscreen /* = false*/)
: width(width), height(height)
{
	int x = SDL_WINDOWPOS_UNDEFINED;
	int y = SDL_WINDOWPOS_UNDEFINED;
	
	int flags = 0;
	
	if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	
	win = SDL_CreateWindow("RobotPenguin", x, y, width, height, flags);
	
	if (win) {
		// Update window size information
		SDL_GetWindowSize(win, &this->width, &this->height);
	}
}

Window::~Window()
{
	if (win) {
		SDL_DestroyWindow(win);
		win = nullptr;
	}
}

int Window::GetWidth()
{
	return width;
}

int Window::GetHeight()
{
	return height;
}

SDL_Window *Window::GetHandle()
{
	return win;
}
