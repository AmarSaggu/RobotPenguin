#pragma once

#include "Window.hpp"
#include "Renderer.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Object.hpp"
#include "Timer.hpp"

#include <vector>

class Game {
	Window win;
	Renderer ren;
	Keyboard key;
	Mouse mouse;
	
	double lag;
	Timer frameTime;
	
	std::vector<Object> objs;
	
	bool quit;
	
	void Input();
	void Update();
	void Render();
	
	void MainLoop();
	
public:
	Game();
	~Game();
	
	void Run();
	
	static const int updateRate = 60;
};
