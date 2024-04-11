#include "Framework/Actor.h"

namespace ly
{
	Actor::Actor(World* world)
		: m_World{world}, m_HasBegunPlay{false}
	{
	}

	Actor::~Actor()
	{
		LOG("Actor Destroyed!");
	}

	void Actor::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
			m_HasBegunPlay = true;
	}

	void Actor::TickInternal(float deltaTime)
	{
	}

	void Actor::BeginPlay()
	{
		BeginPlayInternal();
		LOG("Actor Began Play!");
	}

	void Actor::Tick(float deltaTime)
	{
		TickInternal(deltaTime);
		LOG("Actor is ticking.");
	}
}