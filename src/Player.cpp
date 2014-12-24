#include "Player.hpp"
#include "Keyboard.hpp"
#include "LineSkip.hpp"
#include "View.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <vector>
#include <cmath>

#include <cstdlib>

#define UP    1
#define DOWN  2
#define LEFT  4
#define RIGHT 8

Player::Player()
:x(0), y(0), w(16), h(16), velX(0), velY(0), accX(0), accY(0)
{
	isGrounded = false;
}

void Player::Input(Keyboard *key)
{
	accX = 0;
	accY = 0;

	if (key->IsDown("a")) {
		accX--;
	}
	if (key->IsDown("d")) {
		accX++;
	}
/*	if (key->IsDown("w")) {
		accY--;
	} else { //if (key->IsDown("s")) {
		accY++;
	}*/
	
	if (key->IsDown("space")) {
		if (key->IsDown("w")) {
			accY--;
		}
		if (key->IsDown("s")) {
			accY++;
		}
	} else {
		accY++;
	
		if (isGrounded && key->IsDown("w")) {
			accY -= 16;
			isGrounded = false;
		}
	}
}

int sign(int x)
{
	if (x > 0) {
		return 1;
	} else if (x < 0) {
		return -1;
	} else {
		return 0;
	}
	//return (x / std::abs(x + x == 0));
}

int signer(int x)
{
	if (x == 0) {
		return 0;
	}
	return x / std::abs(x);
}

/*
int Player::GetClosestFace(SDL_Rect rect)
{
	int aX = x + w / 2;
	int aY = y + h / 2;

	int bX = rect.x + rect.w / 2;
	int bY = rect.y + rect.h / 2;

	int a = x - (rect.x + rect.w);
	int b = rect.x - (x + w);

	int c = y - (rect.y + rect.h);
}
*/

/*void Player::HandleCollision(LineSkip *skip, int size)
{
	int minX = x + std::min(0, velX) - 1;
	int minY = y + std::min(0, velY) - 1;
	
	int maxX = x + w + std::max(0, velX) + 17;
	int maxY = y + h + std::max(0, velY) + 17;

	Line line = {minY, maxY};

	//std::cout << "\n\n\nLine = (" << minY << "," << maxY << ")\n";

	for (int x = minX / 17; x < maxX / 17; x++) {
		if (x < 0 || x >= size) {
			continue;
		}
		LineNode *curr = skip[x].GetNode(line);
		for (; curr && curr->line.t < line.b; curr = curr->next[0]) {
			//objects.push_back(curr->line); THIS IS OUR FINAL STAND! WE HANDLE THIS HERE!
		
			SDL_Rect rect = {x * 17, curr->line.t, 18, curr->line.b - curr->line.t};
			
			int distX = std::abs((rect.x + rect.w / 2) - (this->x + this->w / 2)) - rect.w / 2 - this->w / 2;
			int distY = std::abs((rect.y + rect.h / 2) - (this->y + this->h / 2)) - rect.h / 2 - this->h / 2;

			int majorX = distX >= distY ? distX : 0;
			int majorY = distY >= distX ? distY : 0;

			//std::cout << "OBJECT = {" << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << "};\n";
			//std::cout << "Distance = (" << distX << "," << distY << ")\n";

			if (distX >= distY && distX >= 0 && distX - std::abs(velX) < 0) {
				if (velX > 0 && rect.x - (x + w) >= 0) {
					velX = std::min(velX, distX);
				} else if (velX < 0 && x - (rect.x + rect.w) >= 0) {
					velX = std::max(velX, -distX);
				}
			}
			else if (distY >= distX && distY >= 0 && -sign(velY) * distY - (velY) < 0) {
				if (velY > 0) {
					velY = std::min(velY, distY);
				} else if (velY < 0) {
					velY = std::max(velY, -distY);
				}
				//velY = std::min(std::abs(velY), distY) * sign(velY);
			}
		}
	}
}*/

int Player::GetXFace(SDL_Rect rect)
{
	if (x - (rect.x + rect.w) >= 0) {
		return -1;
	} else if (rect.x - (x + w) >= 0) {
		return 1;
	} else {
		return 0;
	}
}

int Player::GetYFace(SDL_Rect rect)
{
	if (y - (rect.y + rect.h) >= 0) {
		return -1;
	} else if (rect.y - (y + h) >= 0) {
		return 1;
	} else {
		return 0;
	}
}

void Player::HandleCollision(LineSkip *skip, int size)
{
	int minX = x + std::min(0, velX) - 1;
	int minY = y + std::min(0, velY) - 1;

	int maxX = x + w + std::max(0, velX);
	int maxY = y + h + std::max(0, velY);

	Line line = {minY, maxY};

	//std::cout << "\n\n-------\n";

	for (int x = minX / 17; x <= (maxX + 16) / 17; x++) {
		if (x < 0 || x >= size) {
			continue;
		}
		LineNode *curr = skip[x].GetNode(line);

		for (; curr && curr->line.t < line.b; curr = curr->next[0]) {
			SDL_Rect rect = {x * 17, curr->line.t, 18, curr->line.b - curr->line.t};

			int distX = std::round(std::abs((rect.x + rect.w / 2.0) - (this->x + this->w / 2.0)) - rect.w / 2.0 - this->w / 2.0);
			int distY = std::round(std::abs((rect.y + rect.h / 2.0) - (this->y + this->h / 2.0)) - rect.h / 2.0 - this->h / 2.0);

			int directionX = GetXFace(rect);
			int directionY = GetYFace(rect);

			//std::cout << "Player = (" << x << "< " << y << ")\n";
			//std::cout << "Rect = {" << rect.x << ", " << rect.y << ", " << rect.w << ", " << rect.h << "}\n";
			//std::cout << "Direction = (" << directionX << ", " << directionY << ")\n";
			//std::cout << "Distance = (" << distX << ", " << distY << ")\n";

			int majorX = distX >= distY ? distX : -1;
			int majorY = distY >= distX ? distY : -1;

			if (majorY >= 0) {
				if (directionY == -sign(velY)) {
					continue;
				}
				velY = sign(velY) * std::min(std::abs(velY), distY);
			}
			else if (majorX >= 0) {
				if (directionX == -sign(velX)) {
					continue;
				}
				velX = sign(velX) * std::min(std::abs(velX), distX);
			}
		}
	}
}

void Player::Logic(LineSkip *skip, int size)
{
	// Simulate drag
	if (accX == 0 && velX != 0) {
		accX = -velX / std::abs(velX);
	}
	if (accY == 0 && velY != 0) {
		accY = -velY / std::abs(velY);
	}
	
	velX += accX;
	velY += accY;
	
	//velX = -200;
	//velY = 200;

	if (velY >= 0) {
		isGrounded = true;
	}

	HandleCollision(skip, size);

	if (velY == 0) isGrounded = true;
	
	//std::cout << "Velocity = (" << velX << "," << velY << ")\n";

	x += velX;
	y += velY;
	
	/*if (y + h / 2 >= 500) {
		y = 500 - h / 2;
		velY = 0;
		isGrounded = true;
	} else {
		//isGrounded = false;
	}*/
}

void Player::Render(SDL_Renderer *ren, View &view)
{
	SDL_Rect rect = {x + view.GetPositionX(), y + view.GetPositionY(), w, h};
	SDL_SetRenderDrawColor(ren, 255, 255, 64, 255);
	SDL_RenderFillRect(ren, &rect);
}
