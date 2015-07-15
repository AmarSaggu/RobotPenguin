#include "Game.hpp"

#include "Window.hpp"
#include "Renderer.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Player.hpp"

#include <SDL2/SDL.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <iostream>

Game::Game()
{
	quit = false;
	
	SDL_Init(SDL_INIT_VIDEO);
	
	win = new Window(1920, 1080, true);
	ren = new Renderer(*win);
	key = new Keyboard;
	mouse = new Mouse;
	
	players.push_back(new Player({100.0, 0.0}, *key, *ren));
	
	// Call update immediately
	lag = 1.0/updateRate;
}

Game::~Game()
{
	for (Player *p : players) {
		delete p;
	}
	players.clear();
	
	delete mouse;
	delete key;
	delete ren;
	delete win;

	SDL_Quit();
}

void Game::Input()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			
			default:
				break;
		}
	}
	
	mouse->Update();

	if (key->IsDown("escape")) {
		quit = true;
	}
	
	for (Player *p : players) {
		p->Input();
	}
}

void Game::Update()
{
	if (mouse->IsDown(Mouse::LEFT)) {
		players.push_back(new Player(mouse->GetPosition(), *key, *ren));
	}
	
	for (Player *p : players) {
		p->Update();
	}
}

void Game::Render()
{
	ren->SetColour(94, 129, 162);
	ren->Clear();
	
	for (Player *p : players) {
		p->Render();
	}
	
	ren->SetColour(152, 176, 78);
	ren->FillRect({win->GetWidth() / 2.0, 750.0}, {(double) win->GetWidth(), 100.0});
	
	ren->Present();
}

void Game::MainLoop()
{
	lag += frameTime.GetElapsedTime();
	
	frameTime.Reset();
	frameTime.Start();

	// Perform logic at constant rate
	while (lag >= 1.0/updateRate) {
		Input();
		Update();
		
		lag -= 1.0/updateRate;
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
