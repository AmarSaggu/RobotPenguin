#pragma once

#include "Timer.hpp"

#include <vector>

class Window;
class Renderer;
class Keyboard;
class Mouse;
class Player;


class Game {
	Window *win;
	Renderer *ren;
	Keyboard *key;
	Mouse *mouse;
	
	std::vector<Player *> players;
	
	bool quit;
	
	double lag;
	Timer frameTime;
	
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
