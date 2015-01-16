#include "Object.hpp"
#include "Vector2D.hpp"
#include "LineArray.hpp"
#include "View.hpp"

#include <SDL2/SDL.h>

static int sign(int x)
{
	return (x > 0) - (x < 0);
}

// Perform integer division with ceiling
static int div_up(int n, int d)
{
	return n / d + (n % d) != 0;
}

Object::Object(Vector2D pos)
: pos(pos), width(32), height(32)
{}

Object::~Object()
{}

/*void Object::HandleWorldCollision(LineArray &world)
{
	Vector2D min;
	min.x = pos.x + std::min(0, vel.x);
	min.y = pos.y + std::min(0, vel.y);

	Vector2D max;
	max.x = pos.x + width  + std::max(0, vel.x);
	max.y = pos.y + height + std::max(0, vel.y);

	Line bounds = {min.y, max.y};

	for (int x = (min.x - 1) / 17; x <= (max.x + (max.x % LINE_SPACING > 0)) / (LINE_SPACING); x++) {
		LineSkip *skip = world.Get(x);

		LineNode *curr = skip->GetNode(bounds);
		for (; curr && curr->line.t < bounds.b; curr = curr->next[0]) {
			
		}
	}
}*/

/*void Object::HandleWorldCollision(LineArray &world)
{
	Vector2D min;
	min.x = pos.x + std::min(0, vel.x);
	min.y = pos.y + std::min(0, vel.y);

	Vector2D max;
	max.x = pos.x + width  + std::max(0, vel.x);
	max.y = pos.y + height + std::max(0, vel.y);

	Line bounds {min.y, max.y};

	Line boundsX {pos.y, pos.y + height};

	// Check X
	for (int x = (min.x - 1) / 17; x <= div_up(max.x, 17); x++) {
		LineSkip &skip = world.Get(x);

		LineNode *curr = skip.GetNode(boundsX.t);

		for (; curr && curr->line.t < boundsX.b; curr = curr->next[0]) {
			//
		}
	}
}*/

// Here's a start on an updated collision algorithm
/*{
	double m = vel.y / (double) vel.x;

	for (int x = pos.x / 17; x != (pos.x + vel.x) / 17; x += sign(vel.x)) {
		Line bounds = pos.y + x * 17 * m;
		
		LineSkip &skip = world.Get(x);

		LineNode *curr = skip
	}
}*/

void Object::Logic(LineArray &world)
{
	// Simulate drag
	if (acc.x == 0) {
		vel.x -= sign(vel.x);
	}
	if (acc.y == 0) {
		vel.y -= sign(vel.y);
	}

	vel += acc;
	
	// Test for collisions
	//HandleWorldCollision(world);

	// Update position
	pos += vel;
}

void Object::Render(SDL_Renderer *ren, View &view)
{
	SDL_Rect rect = {pos.x + view.GetPosition().x, pos.y + view.GetPosition().y, 32, 32};
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderDrawRect(ren, &rect);
}
