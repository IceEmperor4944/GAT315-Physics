#include "spring.h"
#include "body.h"
#include "raymath.h"

void Spring::ApplyForce(float kMultiplier) {
	// Step 1: Calculate direction vector from bodyB to bodyA
	Vector2 direction = bodyA->position - bodyB->position;
	float lengthSquared = Vector2LengthSqr(direction);

	// Avoid division by zero or tiny spring length
	if (lengthSquared < 0.01) return;

	// Step 2: Calculate spring displacement
	float length = sqrtf(lengthSquared);
	float displacement = length - restLength;  // Stretching if > 0, compressed if < 0

	// Step 3: Apply Hooke's Law: F = -k * x
	float forceMagnitude = -(k * kMultiplier) * displacement;

	// Step 4: Normalize direction and calculate spring force vector
	Vector2 normalizedDirection = direction / length;
	Vector2 springForce = normalizedDirection * forceMagnitude;

	// Step 5: Dampen the spring to reduce oscillation
	Vector2 velocityDifference = bodyA->velocity - bodyB->velocity;
	float dampingAmount = Vector2DotProduct(velocityDifference, normalizedDirection) * damping;
	Vector2 dampingForce = normalizedDirection * dampingAmount;

	// Subtract damping from spring force
	Vector2 totalForce = springForce - dampingForce;

	// Step 6: Apply equal and opposite forces to the two bodies
	bodyA->ApplyForce(totalForce);
	bodyB->ApplyForce(Vector2Negate(totalForce));
}

void Spring::Draw(const Scene& scene) {
	scene.DrawLine(bodyA->position, bodyB->position, 3, WHITE);
}