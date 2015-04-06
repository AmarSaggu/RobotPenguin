#pragma once

#include "Window.hpp"
#include "Renderer.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Object.hpp"

#include <vector>

class Game {
	Window win;
	Renderer ren;
	Keyboard key;
	Mouse mouse;
	
	std::vector<Object> objs;
	
	bool quit;
	
	void Input();
	void Update();
	void Render();
	
public:
	Game();
	~Game();
	
	void Run();
};
