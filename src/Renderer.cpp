#include "Renderer.hpp"
#include "Window.hpp"
#include "Vector2D.hpp"

#include <SDL2/SDL.h>

Renderer::Renderer()
: ren(nullptr)
{}

Renderer::~Renderer()
{
	Destroy();
}

bool Renderer::Create(Window &window)
{
	SDL_Window *win = window.GetHandle();
	
	int flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	ren = SDL_CreateRenderer(win, -1, flags);
	
	return ren;
}

void Renderer::Destroy()
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

void Renderer::DrawLine(Vector2D a, Vector2D b)
{
	SDL_RenderDrawLine(ren, a.x, a.y, b.x, b.y);
}

void Renderer::DrawRect(Vector2D pos, Vector2D size)
{
	SDL_Rect rect {pos.x - size.x/2, pos.y - size.y/2, size.x, size.y};
	
	SDL_RenderDrawRect(ren, &rect);
}

void Renderer::FillRect(Vector2D pos, Vector2D size)
{
	SDL_Rect rect {pos.x - size.x/2, pos.y - size.y/2, size.x, size.y};
	
	SDL_RenderFillRect(ren, &rect);
}

SDL_Renderer *Renderer::GetHandle()
{
	return ren;
}
