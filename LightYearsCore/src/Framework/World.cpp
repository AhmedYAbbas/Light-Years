#include "Framework/World.h"
#include "Framework/Actor.h"

namespace ly
{
	World::World()
		: m_HasBegunPlay{false}
	{
	}

	void World::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
			m_HasBegunPlay = true;
	}

	void World::TickInternal(float deltaTime)
	{
		LOG("Tick at framerate %f", 1.f / deltaTime);
		for (auto& actor : m_PendingActors)
		{
			m_Actors.push_back(actor);
			actor->BeginPlay();
		}
		m_PendingActors.clear();

		for (auto it = m_Actors.begin(); it != m_Actors.end();)
		{
			if (it->get()->IsPendingDestroy())
				it = m_Actors.erase(it);
			else
			{
				it->get()->Tick(deltaTime);
				++it;
			}
		}
	}

	void World::BeginPlay()
	{
		BeginPlayInternal();
		LOG("Begin Play!");
	}

	void World::Tick(float deltaTime)
	{
		TickInternal(deltaTime);
	}
}