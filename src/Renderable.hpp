#pragma once

struct Physics;
class Renderer;

class Renderable {
	Physics &physics;
	Renderer &ren;
	int layer;
	
public:
	Renderable(Physics &physics, Renderer &ren, int layer);
	
	void Update();
};
