#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>

#include "Framework/PhysicsSystem.h"
#include "Framework/Actor.h"

namespace ly
{
	Scope<PhysicsSystem> PhysicsSystem::s_Instance = nullptr;

	PhysicsSystem& ly::PhysicsSystem::Get()
	{
		if (!s_Instance)
			s_Instance = Scope<PhysicsSystem> {new PhysicsSystem};

		return *s_Instance;
	}

	void PhysicsSystem::Step(float timeStep)
	{
		m_PhysicsWorld.Step(timeStep, m_VelocityIterations, m_PositionIterations);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->IsPendingDestroy())
			return nullptr;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
		bodyDef.position.Set(listener->GetActorLocation().x * m_PhysicsScale, listener->GetActorLocation().y * m_PhysicsScale);
		bodyDef.angle = Math::DegToRad(listener->GetActorRotation());

		b2PolygonShape shape;
		const auto bounds = listener->GetActorGlobalBounds();
		shape.SetAsBox(bounds.width / 2.f * m_PhysicsScale, bounds.height / 2.f * m_PhysicsScale);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.f;
		fixtureDef.friction = .3f;
		fixtureDef.isSensor = true;

		b2Body* body = m_PhysicsWorld.CreateBody(&bodyDef);
		body->CreateFixture(&fixtureDef);

		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* body)
	{
	}

	PhysicsSystem::PhysicsSystem()
		: m_PhysicsWorld {b2Vec2_zero}, m_PhysicsScale {0.01f}, m_VelocityIterations {8}, m_PositionIterations {3}, m_ContactListener {}
	{
		m_PhysicsWorld.SetContactListener(&m_ContactListener);
		m_PhysicsWorld.SetAllowSleeping(false);
	}

	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* actorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* actorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (actorA && !actorA->IsPendingDestroy())
			actorA->OnActorBeginOverlap(actorB);
		
		if (actorB && !actorB->IsPendingDestroy())
			actorB->OnActorBeginOverlap(actorA);
	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* actorA = nullptr, *actorB = nullptr;
		
		if (contact->GetFixtureA()->GetBody())
			actorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		if (contact->GetFixtureB()->GetBody())
			actorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (actorA && !actorA->IsPendingDestroy())
			actorA->OnActorEndOverlap(actorB);
		if (actorB && !actorB->IsPendingDestroy())
			actorB->OnActorEndOverlap(actorA);

	}
}