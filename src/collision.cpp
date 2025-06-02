#include "collision.h"
#include "math_util.h"
#include <raymath.h>
#include <iostream>

bool Intersects(Body* bodyA, Body* bodyB) {
	float distance = Vector2Distance(bodyA->position, bodyB->position);
	float radius = bodyA->size + bodyB->size;

	return (distance <= radius);
}

void CreateContacts(const bodies_t& bodies, contacts_t& contacts) {
	for (int i = 0; i < bodies.size(); i++) {
		Body* bodyA = bodies[i];
		for (int j = i + 1; j < bodies.size(); j++) {
			Body* bodyB = bodies[j];
			if (bodyA->type != Body::Type::Dynamic && bodyB->type != Body::Type::Dynamic) continue;

			if (Intersects(bodyA, bodyB)) {
				Contact contact;
				contact.bodyA = bodyA;
				contact.bodyB = bodyB;

				Vector2 direction = bodyB->position - bodyA->position;
				float distanceSqr = Vector2LengthSqr(direction);
				if (distanceSqr <= EPSILON) {
					direction = Vector2{ randf(-0.05f, 0.05f), randf(-0.05f, 0.05f) };
					distanceSqr = Vector2LengthSqr(direction);
				}

				float distance = sqrtf(distanceSqr);
				float radius = bodyA->size + bodyB->size;
				contact.depth = radius - distance;
				contact.normal = Vector2Normalize(direction);
				contact.restitution = (bodyA->restitution + bodyB->restitution) / 2;

				contacts.push_back(contact);
			}
		}
	}
}

void SeparateContacts(contacts_t& contacts) {
	for (auto contact : contacts) {
		float totalInverseMass = contact.bodyA->invMass + contact.bodyB->invMass;
		Vector2 separation = contact.normal * (contact.depth / totalInverseMass);
		contact.bodyA->position = contact.bodyA->position + (separation * contact.bodyA->invMass);
		contact.bodyB->position = contact.bodyB->position - (separation * contact.bodyB->invMass);
	}
}

void ResolveContacts(contacts_t& contacts)
{
	for (auto& contact : contacts)
	{
		// compute relative velocity
		Vector2 rv = contact.bodyA->velocity - contact.bodyB->velocity;
		// project relative velocity onto the contact normal
		float nv = Vector2DotProduct(rv, contact.normal);

		// skip if bodies are separating
		if (nv > 0) continue;

		// compute impulse magnitude
		float totalInverseMass = contact.bodyA->invMass + contact.bodyB->invMass;
		float impulseMagnitude = -(1 + contact.restitution) * nv / totalInverseMass;

		// compute impulse vector
		Vector2 impulse = contact.normal * impulseMagnitude;

		// apply impulses to both bodies
		contact.bodyA->ApplyForce(impulse, Body::ForceMode::Impulse);
		contact.bodyB->ApplyForce(Vector2Negate(impulse), Body::ForceMode::Impulse);
	}
}