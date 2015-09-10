#include "Game.hpp"

#include "Window.hpp"
#include "Renderer.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Controller.hpp"
#include "Player.hpp"
#include "System.hpp"

#include <SDL2/SDL.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <iostream>
#include <list>

System<Physics> physicsSystem;
System<Controller> controllerSystem;
System<Renderable> renderableSystem;

void create_player(Vector2D pos, Keyboard &key, Renderer &ren, bool wasd = true)
{
	Physics *physics = physicsSystem.AddComponent((Rect2D) {pos, {16, 8}});
	
	Controller *controller = controllerSystem.AddComponent(*physics, key);
	
	if (!wasd) {
		controller->ArrowKeys();
	}

	renderableSystem.AddComponent(*physics, ren, 1);
}

Game::Game()
{
	quit = false;	

	SDL_Init(SDL_INIT_VIDEO);
	
	win = new Window(1920, 1080, true);
	ren = new Renderer(*win);
	key = new Keyboard;
	mouse = new Mouse;
	
	create_player({100.0, 0.0}, *key, *ren);
	create_player({1000.0, 0.0}, *key, *ren, false);
	
	// Call update immediately
	lag = 1.0/updateRate;
}

Game::~Game()
{
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
	
	controllerSystem.Update();
}

void Game::Update()
{
	if (mouse->IsDown(Mouse::LEFT)) {
		create_player(mouse->GetPosition(), *key, *ren, false);
	}
	if (mouse->IsDown(Mouse::RIGHT)) {
		create_player(mouse->GetPosition(), *key, *ren, true);
	}
	
	physicsSystem.Update();
}

void Game::Render()
{
	ren->SetColour(94, 129, 162);
	ren->Clear();

	renderableSystem.Update();

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
