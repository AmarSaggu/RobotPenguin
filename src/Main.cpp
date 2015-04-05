#include "LineArray.hpp"
#include "LineSkip.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Player.hpp"
#include "Object.hpp"
#include "Timer.hpp"
#include "View.hpp"

#include "Window.hpp"
#include "Renderer.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include <unistd.h>

#define SCREENWIDTH  1920
#define SCREENHEIGHT 1080

#define LINES (100000/LINE_WIDTH)

#define PLAYERS 2000

void render_world(SDL_Renderer *ren, LineArray &skip, View &view);

void explode(LineArray &array, Vector2D point, int radius, bool explode);

void explode(LineArray &array, Vector2D point, int radius, bool explode)
{
	int start = (point.x - radius) / LINE_WIDTH;
	int end   = (point.x + radius) / LINE_WIDTH;
	
	for (int x = start; x <= end; x++) {
		int dx = x * LINE_WIDTH + (LINE_WIDTH / 2) - point.x;
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

	Window window;
	window.Create(SCREENWIDTH, SCREENHEIGHT, true);
		
	Renderer renderer;
	renderer.Create(window);
	
	SDL_Renderer *ren = renderer.GetHandle();
	
	LineArray world;
	
	Keyboard key;
	Mouse mouse;

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

	//auto time = Timer::GetTime();

	Timer frameTime;

	int frame = 0;

	bool quit = false;
	
	int explosionTimer = 100;
	
	while (!quit) {
		frameTime.Start();
		
		SDL_Event event;
		
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}
		
		mouse.Update();

		if (key.IsDown("escape")) {
			quit = true;
		}

		for (size_t i = 0; i < obj.size(); i++) {
			obj[i]->Input(key);
		}
		
		if (key.IsDown("left shift")) {
			for (int i = 0; i < 100; i++) {
			Object *bullet = new Object(player->rect);
			bullet->vel += player->vel;
			bullet->vel.x += rand() % 101 - 49;
			bullet->vel.y += rand() % 101 - 49;
			obj.push_back(bullet);
			}
		}

		for (size_t i = 0; i < obj.size(); i++) {
			obj[i]->Logic(world);
		}
		
		Vector2D viewLocation = player->rect.pos;
		viewLocation += Vector2D(player->rect.w / 2, player->rect.h / 2);
		view.SetPosition(viewLocation);
		
		// Screen to world space
		Vector2D localMouse = mouse.GetPosition();
		localMouse -= view.GetPosition();

		if (mouse.IsDown(Mouse::LEFT)) {
			explode(world, localMouse, 256*2, false);
		} 
		if (mouse.IsDown(Mouse::RIGHT)) {
			explode(world, localMouse, 256*2, true);
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

		renderer.SetColour(202, 193, 251);
		renderer.Clear();
	
		render_world(ren, world, view);
		
		for (size_t i = 0; i < obj.size(); i++) {
			obj[i]->Render(ren, view);
		}

		renderer.Present();
		
		// Update timer
		//auto frametime = Timer::GetTime() - time;
		frameTime.Stop();
		
		if (++frame > 10) {
			std::cout << "FPS: " << 1.0 / frameTime.GetElapsedTime() << std::endl;
			frame = 0;
		}
	}
	
	for (size_t i = 0; i < obj.size(); i++) {
		delete obj[i];
		obj[i] = NULL;
	}
	player = NULL;
		
	SDL_DestroyRenderer(ren);
	//SDL_DestroyWindow(win);
	
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
	minX = minX / LINE_WIDTH;
	maxX = maxX / LINE_WIDTH + (maxX % LINE_WIDTH ? 1 : 0);

	Line bounds = {-offset.y, -offset.y + height};

	for (int x = minX; x < maxX; x++) {
		LineSkip *skip = world.Get(x);
		LineNode *curr = skip->GetNode(bounds);

		for (; curr && curr->line.t < bounds.b; curr = curr->next[0]) {
			SDL_Rect rect = {x * LINE_WIDTH, curr->line.t, LINE_WIDTH + 1, curr->line.b - curr->line.t};

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
