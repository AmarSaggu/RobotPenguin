#include "Controller.hpp"
#include "Physics.hpp"
#include "Keyboard.hpp"
#include "Utils.hpp"

Controller::Controller(Physics &physics, Keyboard &key)
: physics(physics), key(key)
{}

void Controller::Input()
{
	if (key.IsDown("a")) {
		physics.ApplyImpulse({-1.0, 0.0});
	}
	if (key.IsDown("d")) {
		physics.ApplyImpulse({1.0, 0.0});
	}
	
	if (physics.acc.x == 0.0) {
		physics.ApplyImpulse({-sign(physics.vel.x), 0.0});
	}
	
	if (key.IsDown("w") && physics.vel.y == 0.0) {
		physics.ApplyImpulse({0.0, -15.0});
	}
}
