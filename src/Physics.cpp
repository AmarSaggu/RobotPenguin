#include "Physics.hpp"
#include "Utils.hpp"

#include <algorithm>

Physics::Physics(Rect2D box)
: box(box), vel{0, 0}, acc{0, 0}, onGround(false)
{}

void Physics::ApplyImpulse(Vector2D impulse) {
	acc += impulse;
}
	
void Physics::Update() {
	vel += acc;
	acc = {0.0, 0.0};
	
	onGround = false;
	
	// Floor!
	if (box.pos.y + box.size.y/2.0 + vel.y > 700.0) {
		vel.y = 700.0 - (box.pos.y + box.size.y/2.0);
		onGround = true;
	}
	
	box.pos += vel;
}
