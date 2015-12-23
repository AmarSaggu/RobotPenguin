#pragma once

#include "Types.hpp"

#include <cstdint>

struct SDL_Renderer;
class Window;

class Renderer {
	SDL_Renderer *ren;
	
public:
	Renderer(Window &window);
	~Renderer();
	
	void SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255); 
	
	void Clear();
	void Present();
	
	void DrawLine(Vec a, Vec b);
	
	void DrawRect(Vec pos, Vec size);
	void FillRect(Vec pos, Vec size);
	
	SDL_Renderer *GetHandle();
};
