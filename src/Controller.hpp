#pragma once

struct Physics;
class Keyboard;

class Controller {
	Physics &physics;
	Keyboard &key;
	
public:
	Controller(Physics &physics, Keyboard &key);
	
	void Input();
};
