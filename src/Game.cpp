#include "Game.hpp"
#include "Timer.hpp"

#include <SDL2/SDL.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

Game::Game()
{
	quit = false;
	
	SDL_Init(SDL_INIT_VIDEO);
	
	win.Create(640, 480, false);
	ren.Create(win);
	
	objs.push_back(Object({100, 100}, {16, 16}));
	
	// Call update immediately
	lag = 1.0 / updateRate;
}

Game::~Game()
{
	SDL_Quit();
}

void Game::Input()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			
			default:
				break;
		}
	}
	
	mouse.Update();

	if (key.IsDown("escape")) {
		quit = true;
	}
	
	if (mouse.IsDown(mouse.LEFT)) {
		objs.push_back(Object(mouse.GetPosition(), {16, 16}));
	}
	
	for (Object &obj : objs) {
		obj.Input(key);
	}
}

void Game::Update()
{
	for (Object &obj : objs) {
		obj.Update();
	}
}

void Game::Render()
{
	ren.SetColour(255, 255, 125);
	ren.Clear();
	
	ren.SetColour(0, 0, 0);
	ren.DrawLine({0, 400}, {win.GetSize().x, 400});
	
	for (Object &obj : objs) {
		obj.Render(ren);
	}
	
	ren.Present();
}

void Game::MainLoop()
{
	lag += frameTime.GetElapsedTime();
			
	frameTime.Reset();
	frameTime.Start();
	
	Input();
	
	// Perform logic at constant rate
	while (lag >= 1.0 / updateRate) {
		Update();
		
		lag -= 1.0 / updateRate;
	}
	
	Render();
}

void Game::Run()
{
#ifdef EMSCRIPTEN
	emscripten_set_main_loop_arg([](void *data) {
		Game *game = static_cast<Game *>(data);
		game->MainLoop();
	}, this, 0, true);
#else
	while (!quit) {
		MainLoop();
	}
#endif
}
