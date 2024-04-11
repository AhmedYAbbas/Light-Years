#include "Framework/World.h"
#include "Core/Core.h"

namespace ly
{
	World::World()
		: m_BeganPlay{false}
	{
	}

	void World::BeginPlayInternal()
	{
		if (!m_BeganPlay)
		{
			m_BeganPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	void World::BeginPlay()
	{
		LOG("Begin Play!");
	}

	void World::Tick(float deltaTime)
	{
		LOG("Tick at framerate %f", 1.f / deltaTime);
	}
}