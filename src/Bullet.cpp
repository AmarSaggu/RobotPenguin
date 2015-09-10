#include "Bullet.hpp"
#include "Renderer.hpp"

#include <iostream>

Bullet::Bullet(Vector2D pos, Vector2D vel, Renderer &ren)
: lifetime(180)
{
	physics = new Physics({pos, {4.0, 4.0}});
	renderable = new Renderable(*physics, ren, 0);
	physics->ApplyImpulse(vel);
}

Bullet::~Bullet()
{
	delete renderable;
	delete physics;
}

void Bullet::Update()
{
	physics->Update();
	
	//if (obj.rect.pos.x > 1000) {
		//obj.vel *= 0.9;
	//}
	lifetime--;
	
	std::cout << "This should never be seen\n";
}

void Bullet::Render()
{
	renderable->Update();
}

bool Bullet::IsAlive()
{
	return lifetime > 0;
}
