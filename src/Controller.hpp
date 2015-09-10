#pragma once

struct Physics;
class Keyboard;

class Controller {
	Physics &physics;
	Keyboard &key;
	
	int left, right, jump;
	
public:
	Controller(Physics &physics, Keyboard &key);
	
	void Update();
	
	void ArrowKeys();
};
