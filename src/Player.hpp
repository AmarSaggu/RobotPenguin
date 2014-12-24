#pragma once

struct SDL_Renderer;
struct SDL_Rect;


class Keyboard;
class LineSkip;

class Player {
public:
	int x, y;
	int w, h;
	
	int velX, velY;
	int accX, accY;

	bool isGrounded;

	int GetXFace(SDL_Rect rect);
	int GetYFace(SDL_Rect rect);
public:
	Player();
	Player(int x, int y);
	
	void Input(Keyboard *key);
	void HandleCollision(LineSkip *skip, int size);
	void Logic(LineSkip *skip, int size);
	void Render(SDL_Renderer *ren);
};
