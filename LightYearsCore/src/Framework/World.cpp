#include "Framework/World.h"
#include "Framework/Actor.h"
#include "Framework/Application.h"


namespace ly
{
	World::World()
		: m_HasBegunPlay{false}
	{
	}

	void World::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
		{
			m_HasBegunPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		for (auto& actor : m_PendingActors)
		{
			m_Actors.push_back(actor);
			actor->BeginPlayInternal();
		}
		m_PendingActors.clear();

		for (auto it = m_Actors.begin(); it != m_Actors.end();)
		{
			it->get()->TickInternal(deltaTime);
			++it;
		}
		Tick(deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : m_Actors)
			actor->Render(window);
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return Application::Get().GetWindowSize();
	}

	void World::CleanCycle()
	{
		for (auto it = m_Actors.begin(); it != m_Actors.end();)
		{
			if (it->get()->IsPendingDestroy())
				it = m_Actors.erase(it);
			else
				++it;
		}
	}

	void World::BeginPlay()
	{
	}

	void World::Tick(float deltaTime)
	{
	}
}