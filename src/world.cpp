#include "world.h"
#include "body.h"
#include "gui.h"
#include "gravitation.h"

World::~World() {
    DestroyAll();
}

void World::Initialize(Vector2 gravity, size_t poolSize) {
    World::gravity = gravity;
    m_bodies.reserve(poolSize);
}

Body* World::CreateBody(const Vector2& position, float mass, float size, const Color& color) {
    Body* body = new Body(position, mass, size, color);
    m_bodies.push_back(body);
    
    return body;
}

Body* World::CreateBody(Body::Type type, const Vector2& position, float mass, float size, const Color& color) {
    Body* body = new Body(type, position, mass, size, color);
    m_bodies.push_back(body);

    return body;
}

Spring* World::CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping) {
    Spring* spring = new Spring(bodyA, bodyB, restLength, stiffness, damping);
    m_springs.push_back(spring);

    return spring;
}

void World::Step(float timestep) {
    if (!simulate) return;

    if (gravitation > 0) ApplyGravitation(m_bodies, gravitation);

    for (auto spring : m_springs) {
        spring->ApplyForce(springStiffnessMultiplier);
    }

    for (auto body : m_bodies) {
        body->Step(timestep);
        body->ClearForce();
    }
}

void World::Draw(const Scene& scene) {
    for (auto body : m_bodies) {
        body->Draw(scene);
    }

    for (auto spring : m_springs) {
        spring->Draw(scene);
    }
}

void World::DestroyAll() {
    for (auto body : m_bodies) {
        delete body;
    }

    for (auto spring : m_springs) {
        delete spring;
    }
}