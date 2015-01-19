#pragma once

#include "Object.hpp"

class Player: public Object {
public:
	Player(Vector2D pos);
	
	void Input(Keyboard &key);
	//void HandleCollision(LineSkip *skip, int size);
	//void Logic(LineSkip *skip, int size);
	//void Render(SDL_Renderer *ren, View &view);
};
