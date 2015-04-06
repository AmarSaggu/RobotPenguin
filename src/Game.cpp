#include "Game.hpp"
#include "Timer.hpp"

#include <SDL2/SDL.h>

#include <iostream>

Game::Game()
{
	quit = false;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	win.Create(640, 480, false);
	ren.Create(win);
	
	objs.push_back(Object({100, 100}, {16, 16}));
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
	ren.Clear();
	
	ren.DrawLine({0, 400}, {win.GetSize().x, 400});
	
	for (Object &obj : objs) {
		obj.Render(ren);
	}
	
	ren.Present();
}

/*void Game::Run()
{
	Input();
	Update();
	Render();
}*/

void Game::Run()
{		
	double lag = 0.0;
	Timer frameTime;
	
	Timer time;
	time.Start();
	
	while (!quit) {
		lag += frameTime.GetElapsedTime();
				
		frameTime.Reset();
		frameTime.Start();
		
		Input();
		
		// Perform logic at constant rate
		while (lag >= 1.0 / 60.0) {
			Update();
			
			lag -= 1.0 / 60.0;
		}
		
		Render();
		
		std::cout << "FPS = " << 1.0 / frameTime.GetElapsedTime() << std::endl;
	}
}
