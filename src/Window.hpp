#pragma once

struct SDL_Window;

class Window {
	SDL_Window *win;
	int width, height;
	
public:
	Window(int width, int height, bool fullscreen = false);
	~Window();
	
	int GetWidth();
	int GetHeight();
	
	SDL_Window *GetHandle();
};
