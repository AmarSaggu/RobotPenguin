#include "LineArray.hpp"
#include "LineSkip.hpp"
#include "Keyboard.hpp"
#include "Player.hpp"
#include "Object.hpp"
#include "Timer.hpp"
#include "View.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include <unistd.h>

#define SCREENWIDTH  1920
#define SCREENHEIGHT 1080

#define LINEWIDTH 17
#define LINES (1000000/LINEWIDTH)

#define PLAYERS 2000

void render_world(SDL_Renderer *ren, LineArray &skip, View &view);

void explode(LineArray &array, Vector2D point, int radius, bool explode);

void explode(LineArray &array, Vector2D point, int radius, bool explode)
{
	int start = (point.x - radius) / LINEWIDTH;
	int end   = (point.x + radius) / LINEWIDTH;
	
	for (int x = start; x <= end; x++) {
		int dx = x * LINEWIDTH + (LINEWIDTH / 2) - point.x;
		int height = sqrt(radius * radius - dx * dx);
		
		Line line = {point.y - height, point.y + height};
		LineSkip &skip = *array.Get(x);

		if (explode) {
			skip.Sub(line);
	
		} else {
			skip.Add(line);
		}
	}
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	
	uint32_t flags = SDL_WINDOW_SHOWN;
	SDL_Window *win = SDL_CreateWindow("RobotPenguin", 100, 100, SCREENWIDTH, SCREENHEIGHT, flags);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	
	LineArray world;
	
	Keyboard key;

	std::vector<Object*> obj;
	Player *player = new Player({100, 100});
	obj.push_back(player);
	
	for (int i = 0; i < PLAYERS; i++) {
		obj.push_back(new Object({{rand() % 10000, -100}, 16, 16}));
	}

	for (int x = 0; x < LINES; x++) {
		LineSkip *skip = world.Get(x);
		skip->Add((struct Line) {500, 1000000});
	}
	
	View view({Vector2D(0, 0), SCREENWIDTH, SCREENHEIGHT});

	auto time = Timer::GetTime();

	int frame = 0;

	bool quit = false;
	int explosionTimer = 100;
	while (!quit) {
		SDL_Event event;
		
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		Vector2D mouse;
		uint8_t mouseState = SDL_GetMouseState(&mouse.x, &mouse.y);

		if (key.IsDown("escape")) {
			quit = true;
		}

		for (size_t i = 0; i < obj.size(); i++) {
			obj[i]->Input(key);
		}
		
		if (key.IsDown("left shift")) {
			Object *bullet = new Object(player->rect);
			bullet->vel += player->vel;
			bullet->vel.x += 50;
			obj.push_back(bullet);
		}

		for (size_t i = 0; i < obj.size(); i++) {
			obj[i]->Logic(world);
		}
		
		Vector2D viewLocation = player->rect.pos;
		viewLocation += Vector2D(player->rect.w / 2, player->rect.h / 2);
		view.SetPosition(viewLocation);
		
		// Take camera position into account
		mouse.x -= view.GetPosition().x;
		mouse.y -= view.GetPosition().y;

		if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			explode(world, mouse, 256*2, false);
		} else if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			explode(world, mouse, 256*2, true);
		}
		
		if (explosionTimer > 0) {
			--explosionTimer;
		}

		if (explosionTimer == 0 && key.IsDown("space")) {
			for (size_t i = 0; i < obj.size(); i++) {
				explode(world, obj[i]->rect.pos, 100 + rand() % 100, true);
			}
			explosionTimer = 10;
		}

		SDL_SetRenderDrawColor(ren, 202, 193, 251, 255);
		SDL_RenderClear(ren);
	
		render_world(ren, world, view);
		
		for (size_t i = 0; i < obj.size(); i++) {
			obj[i]->Render(ren, view);
		}

		SDL_RenderPresent(ren);
		
		// Update timer
		auto frametime = Timer::GetTime() - time;
		time = Timer::GetTime();
		
		if (++frame > 100) {
			std::cout << "FPS: " << 1.0 / (frametime.count() / 1000000000.0) << std::endl;
			frame = 0;
		}
	}
	
	for (size_t i = 0; i < obj.size(); i++) {
		delete obj[i];
		obj[i] = NULL;
	}
	player = NULL;
		
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	
	SDL_Quit();
		
	return 0;
}

void render_world(SDL_Renderer *ren, LineArray &world, View &view)
{
	Vector2D offset = view.GetPosition();

	int width = view.GetWidth();
	int height = view.GetHeight();

	int minX = -offset.x + 16;
	int maxX = width - offset.x - 16;
	minX = minX / 17;
	maxX = maxX / 17 + (maxX % 17 ? 1 : 0);

	Line bounds = {-offset.y, -offset.y + height};

	for (int x = minX; x < maxX; x++) {
		LineSkip *skip = world.Get(x);
		LineNode *curr = skip->GetNode(bounds);

		for (; curr && curr->line.t < bounds.b; curr = curr->next[0]) {
			SDL_Rect rect = {x * LINEWIDTH, curr->line.t, LINEWIDTH + 1, curr->line.b - curr->line.t};

			rect.x += offset.x;
			rect.y += offset.y;
	
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
			SDL_RenderDrawRect(ren, &rect);
			
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
