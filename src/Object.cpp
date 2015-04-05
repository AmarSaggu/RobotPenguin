#include "Object.hpp"

#include "Keyboard.hpp"
#include "Rect2D.hpp"
#include "Vector2D.hpp"
#include "LineArray.hpp"
#include "View.hpp"

#include <SDL2/SDL.h>

static int sign(int x)
{
	return (x > 0) - (x < 0);
}

Object::Object(Rect2D rect)
: rect(rect)
{}

Object::~Object()
{}

void Object::Input(Keyboard &key)
{
	acc.x = rand() % 3 - 1;
	acc.y = 1;

	if (rand() % 100 == 0) {
		acc.y = -20;
	}
}

void Object::Logic(LineArray &world)
{
	// Simulate drag
	if (acc.x == 0) {
		vel.x -= sign(vel.x);
	}
	//if (acc.y == 0) {
	//	vel.y -= sign(vel.y);
	//}

	vel += acc;
	
	// Test for collisions
	HandleWorldCollision(world);

	// Update position
	rect.pos += vel;
}

void Object::Render(SDL_Renderer *ren, View &view)
{
	SDL_Rect drawRect = {rect.pos.x + view.GetPosition().x, rect.pos.y + view.GetPosition().y, rect.w, rect.h};
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderDrawRect(ren, &drawRect);
}

void Object::HandleWorldCollision(LineArray &world)
{
	// Find the bounding box
	Vector2D min;
	min.x = rect.pos.x + std::min(0, vel.x);
	min.y = rect.pos.y + std::min(0, vel.y);

	Vector2D max;
	max.x = rect.pos.x + rect.w + std::max(0, vel.x);
	max.y = rect.pos.y + rect.h + std::max(0, vel.y);

	Line bounds {min.y, max.y};

	min.x -= 1; // lines are a pixel wider than they are spaced
	max.x += LINE_WIDTH - 1; // round up the max division 

	for (int x = min.x / LINE_WIDTH; x <= max.x / LINE_WIDTH; x++) {
		LineSkip &skip = *world.Get(x);
		LineNode *curr = skip.GetNode(bounds);

		for (; curr && curr->line.t < bounds.b; curr = curr->next[0]) {
			Rect2D lineRect {{x * LINE_WIDTH, curr->line.t}, LINE_WIDTH + 1, curr->line.b - curr->line.t};

			// Use the distance as the minimum displacement vector,
			// since we assume everything is a collision
			Vector2D dist = rect.GetDistance(lineRect);
			
			if (dist.x >= dist.y) {
				vel.x = std::min(dist.x, std::abs(vel.x)) * sign(vel.x);
			}
			if (dist.x <= dist.y) {
				vel.y = std::min(dist.y, std::abs(vel.y)) * sign(vel.y);
			}
		}
	}
}

/*void Object::HandleWorldCollision(LineArray &world)
{
	if (rect.pos.y  + vel.y > 100) {
		rect.pos.y = 100;
		vel.y = std::min(vel.y, 0);
	}
	//rect.pos.y = std::min(100, rect.pos.y);
}*/
