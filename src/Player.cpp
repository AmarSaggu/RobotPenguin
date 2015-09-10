#include "Player.hpp"

#include "Physics.hpp"
#include "Controller.hpp"
#include "Renderable.hpp"

Player::Player(Physics *p, Controller *c, Renderable *r)
: physics(p), controller(c), renderable(r)
{}

//void Player::Input()
//{
	/*if (mouse.IsDown(Mouse::LEFT)) {
		Vector2D direction = mouse.GetPosition() - obj.rect.pos;
	
		direction /= direction.GetLength();
		direction *= 25.0;
	
		Bullet bullet(obj.rect.pos,*/ /*obj.vel +*/ /*direction);
		bullets.push_back(bullet);
	}*/
//}

//void Player::Update()
//{
	/*for (Bullet &b : bullets) {
		b.Update();
	}*/
	
	/*for (int i = bullets.size() - 1; i >= 0; i--) {	
		if (!bullets[i].IsAlive()) {
			bullets.erase(bullets.begin() + i);
		}
	}*/
//}

//void Player::Render()
//{
	/*for (size_t i = 1; i < bullets.size(); i++) {
		if (bullets[i-1].lifetime + 1 != bullets[i].lifetime) {
			continue;
		}
		
		Vector2D a = bullets[i-1].obj.rect.pos;
		Vector2D b = bullets[i-0].obj.rect.pos;
		
		reen.DrawLine(a, b);
	}*/
	
	//for (Bullet &b : bullets) {
		//b.Render(reen);
	//}
//}
