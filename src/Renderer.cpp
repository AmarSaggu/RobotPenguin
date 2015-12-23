#include "Renderer.hpp"

#include "Window.hpp"

#include <SDL2/SDL.h>

#include <cmath>

Renderer::Renderer(Window &window)
{
	SDL_Window *win = window.GetHandle();
	
	int flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	ren = SDL_CreateRenderer(win, -1, flags);
}

Renderer::~Renderer()
{
	if (ren) {
		SDL_DestroyRenderer(ren);
		ren = nullptr;
	}
}

void Renderer::SetColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a /*= 255*/)
{
	SDL_SetRenderDrawColor(ren, r, g, b, a);
}
	
void Renderer::Clear()
{
	SDL_RenderClear(ren);
}

void Renderer::Present()
{
	SDL_RenderPresent(ren);
}

void Renderer::DrawLine(Vec a, Vec b)
{
	SDL_RenderDrawLine(ren, a.x, a.y, b.x, b.y);
}

static SDL_Rect vec_to_rect(Vec pos, Vec size)
{
	SDL_Rect rect;
	rect.x = std::round(pos.x - size.x/2.0);
	rect.y = std::round(pos.y - size.y/2.0);
	rect.w = std::round(size.x);
	rect.h = std::round(size.y);
	
	return rect;
}

void Renderer::DrawRect(Vec pos, Vec size)
{
	SDL_Rect rect = vec_to_rect(pos, size);
	SDL_RenderDrawRect(ren, &rect);
}

void Renderer::FillRect(Vec pos, Vec size)
{
	SDL_Rect rect = vec_to_rect(pos, size);
	SDL_RenderFillRect(ren, &rect);
}

SDL_Renderer *Renderer::GetHandle()
{
	return ren;
}
