#include "Renderable.hpp"

#include "Renderer.hpp"
#include "Physics.hpp"

Renderable::Renderable(Physics &physics, Renderer &ren, int layer)
: physics(physics), ren(ren), layer(layer)
{}

void Renderable::Update()
{
	ren.SetColour(255, 255, 255);
	ren.DrawRect(physics.box.pos, physics.box.size);
}
