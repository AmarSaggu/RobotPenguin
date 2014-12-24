#include "LineSkip.hpp"
#include "Keyboard.hpp"
#include "Player.hpp"
#include "Timer.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <unistd.h>

#define SCREENWIDTH 1024
#define SCREENHEIGHT 768

#define LINEWIDTH 17
#define LINES (SCREENWIDTH/LINEWIDTH)

#define PLAYERS 1

void render_skip(SDL_Renderer *ren, int x, LineSkip *skip);

void explode(LineSkip *skip, int x, int y, int radius);
void replode(LineSkip *skip, int x, int y, int radius);

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	
	uint32_t flags = SDL_WINDOW_SHOWN;//SDL_WINDOW_FULLSCREEN_DESKTOP;
	SDL_Window *win = SDL_CreateWindow("Mana", 100, 100, SCREENWIDTH, SCREENHEIGHT, flags);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	
	LineSkip skip[LINES];
	
	Keyboard key;

	Player players[PLAYERS];
	
	for (int i = 0; i < PLAYERS; i++) {
		players[i].x = rand() % SCREENWIDTH;
		players[i].y = rand() % SCREENHEIGHT;
	}
	
	players[0].x = 400;
	players[0].y = 100;

	skip[40/LINEWIDTH].Add((struct Line) {250, 350});
	
	skip[320/LINEWIDTH].Add((struct Line) {350, 355});

	//usleep(1000*1000);

	auto time = Timer::GetTime();

	bool quit = false;

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
		

		int mouse_x, mouse_y;
		uint8_t mouse = SDL_GetMouseState(&mouse_x, &mouse_y);

		if (mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			replode(skip, mouse_x, mouse_y, 256);
		} else if (mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			//skip[mouse_x/WIDTH].Sub((struct Line) {mouse_y - 20, mouse_y + 20});
			explode(skip, mouse_x, mouse_y, 256);
		}

		if (key.IsDown("w")) {
			SDL_SetRenderDrawColor(ren, rand() % 256, rand() % 256, rand() % 256, 255);
		}
		
		if (key.IsDown("escape")) {
			quit = true;
		}

		for (int i = 0; i < PLAYERS; i++) {
			players[i].Input(&key);
		}

		for (int i = 0; i < PLAYERS; i++) {
			players[i].Logic(skip, LINES);
		}

		SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
		SDL_RenderClear(ren);
		
		for (int i = 0; i < LINES; i++) {
			render_skip(ren, i, &skip[i]);
		}
		
		for (int i = 0; i < PLAYERS; i++) {
			players[i].Render(ren);
		}

		SDL_RenderPresent(ren);
		usleep(10000);
		
		auto frametime = Timer::GetTime() - time;
		
		auto moo = std::chrono::duration_cast<std::chrono::nanoseconds>(Timer::GetTime() - time);
		//std::cout << "FPS: " << 1.0 / (moo.count() / 1000000000.0) << std::endl;
		
		time = Timer::GetTime();
	}
		
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	
	SDL_Quit();
		
	return 0;
}

void render_skip(SDL_Renderer *ren, int x, LineSkip *skip)
{
	Line view = {0, SCREENHEIGHT};
	
	LineNode *curr = skip->GetNode(view);
		
	for (; curr && curr->line.t < view.b; curr = curr->next[0]) {
		Line line = curr->line;
		
		SDL_Rect rect = {x * LINEWIDTH, line.t, LINEWIDTH + 1, line.b - line.t};

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);		
		SDL_RenderFillRect(ren, &rect);
		
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
