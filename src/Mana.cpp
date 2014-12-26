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

void render_lines(SDL_Renderer *ren, LineSkip *skip, int size, View &view);

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

	//usleep(1000*1000);

	auto time = Timer::GetTime();

	bool quit = false;

	View view(0, 0, SCREENWIDTH, SCREENHEIGHT);
	
	SDL_Window *map_win = SDL_CreateWindow("Map!", 100, 100, 1920, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer *map_ren = SDL_CreateRenderer(map_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	int mapX = 0;
	int mapY = 0;

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

		if (key.IsDown("w")) {
			SDL_SetRenderDrawColor(ren, rand() % 256, rand() % 256, rand() % 256, 255);
		}
		
		if (key.IsDown("escape")) {
			quit = true;
		}

		for (int i = 0; i < 1; i++) {
			players[i].Input(&key);
		}
		
		const int FACTOR = 20;
		
		if (key.IsDown("left")) {
			mapX -= FACTOR;
		}
		if (key.IsDown("right")) {
			mapX += FACTOR;
		}
		if (key.IsDown("up")) {
			mapY -= FACTOR;
		}
		
		if (key.IsDown("down")) {
			mapY += FACTOR;
		}

		for (int i = 0; i < PLAYERS; i++) {
			if (i > 0) players[i].accY = 1;
			players[i].Logic(skip, LINES);
		}
		
		
		for (int i = 0 ; i < 100; i++) {
			int lucky = 1 + (rand() % (PLAYERS - 1));
			explode(skip, players[lucky].x, players[lucky].y, 256/2);
			players[lucky].x = rand() % 100000;
			players[lucky].y = -1000;	
		}
	
		view.SetPosition(players[0].x, players[0].y);
		
		mouse_x -= view.GetPositionX();
		mouse_y -= view.GetPositionY();

		if (mouse & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			replode(skip, mouse_x, mouse_y, 256*2);
		} else if (mouse & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			//skip[mouse_x/WIDTH].Sub((struct Line) {mouse_y - 20, mouse_y + 20});
			explode(skip, mouse_x, mouse_y, 256*2);
		}

		SDL_SetRenderDrawColor(ren, 202, 193, 251, 255);
		SDL_RenderClear(ren);
		
		render_lines(ren, skip, LINES, view); 	

		for (int i = 0; i < 1; i++) {
			players[i].Render(ren, view);
		}

		SDL_RenderPresent(ren);
		//usleep(10000);
		
		
		//mapX = players[0].x / 17;
		{
			SDL_SetRenderDrawColor(map_ren, 255, 255, 255, 255);
			SDL_RenderClear(map_ren);
			
			Line bounds = {0, 800 * 17};
			
			SDL_SetRenderDrawColor(map_ren, 0, 0, 0, 255);
			
			for (int x = mapX; x < mapX + 1920; x++) {
				if (x < 0 || x >= LINES) {
					continue;
				}
				
				LineNode *curr = skip[x].GetNode(bounds);
				
				while (curr && curr->line.t <= bounds.b) {
					Line line = curr->line;
					SDL_Rect rect = {x, line.t / 17, 1, (line.b - line.t) / 17};
					rect.x -= mapX;
					rect.y -= mapY;
					
					SDL_RenderFillRect(map_ren, &rect);
					
					curr = curr->next[0];
				}
			}
			
			SDL_RenderPresent(map_ren);
		}
		
		auto frametime = Timer::GetTime() - time;
		
		auto moo = std::chrono::duration_cast<std::chrono::nanoseconds>(Timer::GetTime() - time);
		std::cout << "FPS: " << 1.0 / (moo.count() / 1000000000.0) << std::endl;
		
		time = Timer::GetTime();
	}
	
	SDL_DestroyRenderer(map_ren);
	SDL_DestroyWindow(map_win);
		
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	
	SDL_Quit();
		
	return 0;
}

void render_lines(SDL_Renderer *ren, LineSkip *skip, int size, View &view)
{
	int offsetX = view.GetPositionX();
	int offsetY = view.GetPositionY();

	int width = view.GetWidth();
	int height = view.GetHeight();

	int minX = -offsetX + 16;
	int maxX = width - offsetX - 16;
	minX = minX / 17;
	maxX = maxX / 17 + (maxX % 17 ? 1 : 0);

	Line bounds =  {-offsetY, -offsetY + height};
	
	//std::cout << "Bounds = {" << bounds.t << ", " << bounds.b << std::endl;

	for (int x = minX; x < maxX; x++) {
		if (x < 0 || x >= size) {
			continue;
		}
		
		LineNode *curr = skip[x].GetNode(bounds);

		for (; curr && curr->line.t < bounds.b; curr = curr->next[0]) {
			SDL_Rect rect = {x * LINEWIDTH, curr->line.t, LINEWIDTH + 1, curr->line.b - curr->line.t};

			rect.x += offsetX;
			rect.y += offsetY;

			//SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
			//SDL_RenderFillRect(ren, &rect);

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

void render_skip(SDL_Renderer *ren, int x, LineSkip &skip)
{
	Line view = {0, SCREENHEIGHT};
	
	LineNode *curr = skip.GetNode(view);
		
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

/*void create_image(LineSkip *skip, int size, Line bounds)
{
	
}*/

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
