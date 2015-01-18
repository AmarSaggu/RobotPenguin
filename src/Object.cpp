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

// Perform integer division with ceiling
static int div_up(int n, int d)
{
	return n / d + ((n % d) != 0);
}

Object::Object(Rect2D rect)
: rect(rect)
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

void Object::Input(Keyboard &key)
{
	acc.x = 0;
	acc.y = 0;

	if (key.IsDown("left")) {
		acc.x--;
	}
	if (key.IsDown("right")) {
		acc.x++;
	}
	if (key.IsDown("up")) {
		acc.y--;
	}
	if (key.IsDown("down")) {
		acc.y++;
	}
}

void Object::HandleWorldCollision(LineArray &world)
{
	Vector2D min;
	min.x = rect.pos.x + std::min(0, vel.x);
	min.y = rect.pos.y + std::min(0, vel.y);

	Vector2D max;
	max.x = rect.pos.x + rect.w + std::max(0, vel.x);
	max.y = rect.pos.y + rect.h + std::max(0, vel.y);

	Line bounds {min.y, max.y};

	for (int x = (min.x - 1) / 17; x < (max.x + 16) / 17; x++) {
		LineSkip &skip = *world.Get(x);
		LineNode *curr = skip.GetNode(bounds);

		for (; curr && curr->line.t < bounds.b; curr = curr->next[0]) {
			Rect2D lineRect {{x * 17, curr->line.t}, 18, curr->line.b - curr->line.t};

			Vector2D dist = rect.GetDistance(lineRect);
			
			if (dist.x >= dist.y) {
				vel.x = std::min(dist.x, std::abs(vel.x)) * sign(vel.x);
			}
			elseif (dist.x <= dist.y) {
				vel.y = std::min(dist.y, std::abs(vel.y)) * sign(vel.y);
			}
		}
	}
}

// Here's a start on an updated collision algorithm
/*{
	double m = vel.y / (double) vel.x;

	for (int x = pos.x / 17; x != (pos.x + vel.x) / 17; x += sign(vel.x)) {
		Line bounds = pos.y + x * 17 * m;
		
		LineSkip &skip = world.Get(x);

		LineNode *curr = skip
	}
}*/

/*void Object::HandleWorldCollision(LineArray &world)
{
	//
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
