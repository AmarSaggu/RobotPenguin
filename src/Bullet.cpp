#include "Bullet.hpp"

Bullet::Bullet(Vector2D pos, Vector2D vel)
: lifetime(180)
{
	physics = new Physics({pos, {4.0, 4.0}});
	physics->ApplyImpulse(vel);
}

Bullet::~Bullet()
{
	delete physics;
}

void Bullet::Update()
{
	physics->Update();
	
	//if (obj.rect.pos.x > 1000) {
		//obj.vel *= 0.9;
	//}
	lifetime--;
}

void Bullet::Render(Renderer &ren)
{
	//obj.Render(ren);
}

bool Bullet::IsAlive()
{
	return lifetime > 0;
}
