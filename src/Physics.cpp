#include "Physics.hpp"
#include "Utils.hpp"

#include <algorithm>

Physics::Physics(Rect2D box)
: box(box)
{}

void Physics::ApplyImpulse(Vector2D impulse) {
	acc += impulse;
}
	
void Physics::Update() {
	vel += acc;
	acc = {0.0, 0.0};
	
	// Floor!
	if (box.pos.y + vel.y > 700.0) {
		vel.y = 700.0 - box.pos.y;
	}
	
	box.pos += vel;
}
