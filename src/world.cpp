#include "world.h"
#include "body.h"
#include "collision.h"
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

Body* World::CreateBody(Body::Type type, Body::Shape shape, const Vector2& position, float mass, float size, const Color& color) {
    Body* body = new Body(type, shape, position, mass, size, color);
    m_bodies.push_back(body);

    return body;
}

//Body* World::CreateBody(Body::Type type, const Vector2& cornerA, const Vector2& cornerB, float mass, const Color& color) {
//    Body* body = new Body(type, cornerA, cornerB, mass, color);
//    m_bodies.push_back(body);
//
//    return body;
//}

Spring* World::CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping) {
    Spring* spring = new Spring(bodyA, bodyB, restLength, stiffness, damping);
    m_springs.push_back(spring);

    return spring;
}

void World::Step(float timestep)
{
    if (!simulate) return;

    if (gravitation > 0) ApplyGravitation(m_bodies, gravitation);

    for (auto spring : m_springs)
    {
        spring->ApplyForce(springStiffnessMultiplier);
    }

    // body integration
    for (auto body : m_bodies)
    {
        body->Step(timestep);
        body->ClearForce();
    }

    // contact solver
    for (int i = 0; i < 5; i++)
    {
        CreateContacts(m_bodies, m_contacts);
        SeparateContacts(m_contacts);
        ResolveContacts(m_contacts);
        m_contacts.clear();
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

    m_bodies.clear();
    m_springs.clear();
    m_contacts.clear();
}