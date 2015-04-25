#pragma once

#include "Vector2D.hpp"

#include <stdint.h>

struct SDL_Renderer;
class Window;

class Renderer {
	SDL_Renderer *ren;
public:
	Renderer();
	~Renderer();
	
	bool Create(Window &window);
	void Destroy();
	
	void SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255); 
	
	void Clear();
	void Present();
	
	void DrawLine(Vector2D a, Vector2D b);
	
	void DrawRect(Vector2D pos, Vector2D size);
	void FillRect(Vector2D pos, Vector2D size);
	
	SDL_Renderer *GetHandle();
};
