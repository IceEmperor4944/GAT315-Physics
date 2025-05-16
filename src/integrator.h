#pragma once
#include "body.h"
#include "raymath.h"

inline void ExplicitIntegrator(Body& body, float timestep) {
	body.position += (body.velocity * timestep);
	body.velocity += (body.acceleration * timestep);
	body.velocity *= 1.0f / (1.0f + (body.damping * timestep));
}

inline void SemiImplicitIntegrator(Body& body, float timestep) {
	body.velocity += (body.acceleration * timestep);
	body.position += (body.velocity * timestep);
	body.velocity *= 1.0f / (1.0f + (body.damping * timestep));
}