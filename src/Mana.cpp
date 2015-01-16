#include "LineSkip.hpp"
#include "Keyboard.hpp"
#include "Player.hpp"
#include "Timer.hpp"
#include "View.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <unistd.h>

#define SCREENWIDTH  1920
#define SCREENHEIGHT 1080

#define LINEWIDTH 17
#define LINES (1000000/LINEWIDTH)

#define PLAYERS 100000


void render_shadows(SDL_Renderer *ren, LineSkip *skip, int size, View &view);
void render_lines(SDL_Renderer *ren, LineSkip *skip, int size, View &view);

// Remove or add Lines within a circle
void explode(LineSkip *skip, int x, int y, int radius);
void replode(LineSkip *skip, int x, int y, int radius);

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	
	uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN;
	SDL_Window *win = SDL_CreateWindow("Mana", 100, 100, SCREENWIDTH, SCREENHEIGHT, flags);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	
	LineSkip skip[LINES];
	
	Keyboard key;

	Player players[PLAYERS];
	
	for (int i = 0; i < PLAYERS; i++) {
		players[i].x = rand() % 100000;
		players[i].y = -1000;
	}
	
	players[0].x = 400;
	players[0].y = 100;

	skip[40/LINEWIDTH].Add((struct Line) {250, 350});
	skip[320/LINEWIDTH].Add((struct Line) {350, 355});

	for (int x = 0; x < LINES; x++) {
		skip[x].Add((struct Line) {500, 1000000});
	}

	auto time = Timer::GetTime();

	bool quit = false;

	View view(Vector2D(0, 0), SCREENWIDTH, SCREENHEIGHT);

	while (!quit) {
		SDL_Event event;
		
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			/*if (event.type == SDL_KEYDOWN) {
				puts(SDL_GetKeyName(event.key.keysym.sym));
			}*/
		}

		Vector2D mouse;
		uint8_t mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);

		if (key.IsDown("escape")) {
			quit = true;
		}

		for (int i = 0; i < 1; i++) {
			players[i].Input(&key);
		}

		for (int i = 0; i < PLAYERS; i++) {
			if (i > 0) players[i].accY = 1;
			players[i].Logic(skip, LINES);
		}
		
		// Randomly teleport players to the sky 
		for (int i = 0 ; i < 100; i++) {
			int lucky = 1 + (rand() % (PLAYERS - 1));
			explode(skip, players[lucky].x, players[lucky].y, 256/2);
			players[lucky].x = rand() % 100000;
			players[lucky].y = -1000;	
		}
	
		view.SetPosition(Vector2D(players[0].x, players[0].y));
		
		// Take camera position into account
		mouse.x -= view.GetPosition().x;
		mouse.y -= view.GetPosition().y;

		if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			replode(skip, mouse.x, mouse.y, 256*2);
		} else if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			explode(skip, mouse.x, mouse.y, 256*2);
		}

		SDL_SetRenderDrawColor(ren, 202, 193, 251, 255);
		SDL_RenderClear(ren);
	
		render_shadows(ren, skip, LINES, view);	
		render_lines(ren, skip, LINES, view); 	

		for (int i = 0; i < PLAYERS; i++) {
			players[i].Render(ren, view);
			break; // Only render the first player entity
		}

		SDL_RenderPresent(ren);
		
		// Update timer
		auto frametime = Timer::GetTime() - time;
		time = Timer::GetTime();
		std::cout << "FPS: " << 1.0 / (frametime.count() / 1000000000.0) << std::endl;
	}
		
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	
	SDL_Quit();
		
	return 0;
}

void render_shadows(SDL_Renderer *ren, LineSkip *skip, int size, View &view)
{
	int offsetX = view.GetPosition().x;
	int offsetY = view.GetPosition().y;

	int width = view.GetWidth();
	int height = view.GetHeight();

	int minX = -offsetX + 16;
	int maxX = width - offsetX - 16;
	minX = minX / 17;
	maxX = maxX / 17 + (maxX % 17 ? 1 : 0);

	Line bounds =  {-offsetY, -offsetY + height};

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

	for (int x = minX; x < maxX; x++) {
		if (x < 0 || x >= size) {
			continue;
		}
		
		LineNode *curr = skip[x].GetNode(bounds);

		for (; curr && curr->line.t < bounds.b; curr = curr->next[0]) {
			SDL_Rect rect = {x * LINEWIDTH, curr->line.t, LINEWIDTH + 1, curr->line.b - curr->line.t};

			rect.x += offsetX;
			rect.y += offsetY;
			
			SDL_RenderDrawRect(ren, &rect);
		}
	}
}
void render_lines(SDL_Renderer *ren, LineSkip *skip, int size, View &view)
{
	int offsetX = view.GetPosition().x;
	int offsetY = view.GetPosition().y;

	int width = view.GetWidth();
	int height = view.GetHeight();

	int minX = -offsetX + 16;
	int maxX = width - offsetX - 16;
	minX = minX / 17;
	maxX = maxX / 17 + (maxX % 17 ? 1 : 0);

	Line bounds =  {-offsetY, -offsetY + height};
	
	for (int x = minX; x < maxX; x++) {
		if (x < 0 || x >= size) {
			continue;
		}
		
		LineNode *curr = skip[x].GetNode(bounds);

		for (; curr && curr->line.t < bounds.b; curr = curr->next[0]) {
			SDL_Rect rect = {x * LINEWIDTH, curr->line.t, LINEWIDTH + 1, curr->line.b - curr->line.t};

			rect.x += offsetX;
			rect.y += offsetY;

			rect.x++;
			rect.y++;
			rect.w -= 2;
			rect.h -= 2;

			if (x % 2) {
				SDL_SetRenderDrawColor(ren, 176, 236, 169, 255);
			} else {
				SDL_SetRenderDrawColor(ren, 94, 255, 212, 255);
			}
			SDL_RenderFillRect(ren, &rect);
		}
	}
}

void explode(LineSkip *skip, int point_x, int point_y, int radius)
{
	int start = std::max(0, (point_x - radius) / LINEWIDTH);
	start = std::min(start, LINES);
	
	int end = std::max(0, (point_x + radius) / LINEWIDTH) + 1;
	end = std::min(end, LINES);
	
	for (int x = start; x < end; x++) {
		int moo = x * LINEWIDTH + (LINEWIDTH / 2) - point_x;
		
		int height = sqrt(radius * radius - moo * moo);
		
		struct Line line = {point_y - height, point_y + height};
		
		skip[x].Sub(line);
	}	
}

void replode(LineSkip *skip, int point_x, int point_y, int radius)
{
	int start = std::max(0, (point_x - radius) / LINEWIDTH);
	start = std::min(start, LINES);
	
	int end = std::max(0, (point_x + radius) / LINEWIDTH) + 1;
	end = std::min(end, LINES);
	
	for (int x = start; x < end; x++) {
		int moo = x * LINEWIDTH + (LINEWIDTH / 2) - point_x;
		
		int height = sqrt(radius * radius - moo * moo);
		
		struct Line line = {point_y - height, point_y + height};
		
		skip[x].Add(line);
	}	
}
