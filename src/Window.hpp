#pragma once

#include "Vector2D.hpp"

struct SDL_Window;
struct SDL_Renderer;

class Window {
	SDL_Window *win;
	
	Vector2D size;
	
public:
	Window();
	~Window();
	
	bool Create(int width, int height, bool fullscreen = false);
	void Destroy();
	
	Vector2D GetSize();
	
	SDL_Window *GetHandle();
};
