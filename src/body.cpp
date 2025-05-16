#include "world.h"
#include "integrator.h"
#include "raymath.h"

void Body::Step(float dt) {
	if (type != Type::Dynamic) return;

	//apply gravity
	force += (World::gravity * gravityScale) * mass;
	//compute acceleration
	acceleration = (force * invMass);

	SemiImplicitIntegrator(*this, dt);
}

void Body::Draw(const Scene& scene) {
	scene.DrawCircle(position, size, color);
}

void Body::ApplyForce(const Vector2& force) {
	this->force += force;
}