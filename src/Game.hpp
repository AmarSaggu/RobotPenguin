#pragma once

#include "Timer.hpp"

#include <vector>

class Window;
class Renderer;
class Keyboard;
class Mouse;

class Game {
	bool quit;
	
	double lag;
	Timer frameTime;
	
	Window *win;
	Renderer *ren;
	Keyboard *key;
	Mouse *mouse;
	
	void Input();
	void Update();
	void Render();
	
	void MainLoop();
	
public:
	Game();
	~Game();
	
	void Run();
	
	static constexpr double updateRate = 60.0;
};
