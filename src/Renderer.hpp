#pragma once

#include "Vector2D.hpp"

#include <cstdint>

struct SDL_Renderer;
class Window;

class Renderer {
	SDL_Renderer *ren;
	
public:
	Renderer(Window &window);
	~Renderer();
	
	void SetColour(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255); 
	
	void Clear();
	void Present();
	
	void DrawLine(Vector2D a, Vector2D b);
	
	void DrawRect(Vector2D pos, Vector2D size);
	void FillRect(Vector2D pos, Vector2D size);
	
	SDL_Renderer *GetHandle();
};
