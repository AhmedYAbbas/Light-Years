#include "Framework/World.h"
#include "Framework/Actor.h"
#include "Framework/Application.h"
#include "Gameplay/GameStage.h"
#include "Widget/HUD.h"

namespace ly
{
	World::World()
		: m_HasBegunPlay{false}, m_CurrentStage{m_GameStages.end()}
	{
	}

	void World::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
		{
			m_HasBegunPlay = true;
			BeginPlay();
			InitGameStages();
			StartStages();
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

		if (m_CurrentStage != m_GameStages.end())
			m_CurrentStage->get()->TickStage(deltaTime);

		Tick(deltaTime);

		if (m_HUD)
		{
			if (!m_HUD->IsInit())
				m_HUD->NativeInit(Application::Get().GetWindow());
			m_HUD->Tick(deltaTime);
		}
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : m_Actors)
			actor->Render(window);

		RenderHUD(window);
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

	void World::AddStage(const Ref<GameStage>& stage)
	{
		m_GameStages.push_back(stage);
	}

	bool World::DispatchEvent(const sf::Event& event)
	{
		if (m_HUD)
			return m_HUD->HandleEvent(event);

		return false;
	}

	void World::BeginPlay()
	{
	}

	void World::Tick(float deltaTime)
	{
	}

	void World::InitGameStages()
	{
	}

	void World::AllGameStagesFinished()
	{
		LOG("All Stages Finished!");
	}

	void World::RenderHUD(sf::RenderWindow& window)
	{
		if (m_HUD)
			m_HUD->Draw(window);
	}

	void World::NextGameStage()
	{
		m_CurrentStage = m_GameStages.erase(m_CurrentStage);
		if (m_CurrentStage != m_GameStages.end())
		{
			m_CurrentStage->get()->StartStage();
			m_CurrentStage->get()->OnStageFinished.Bind(GetWeakRef(), &World::NextGameStage);
		}
		else
			AllGameStagesFinished();
	}
	void World::StartStages()
	{
		m_CurrentStage = m_GameStages.begin();
		if (m_CurrentStage != m_GameStages.end())
		{
			m_CurrentStage->get()->StartStage();
			m_CurrentStage->get()->OnStageFinished.Bind(GetWeakRef(), &World::NextGameStage);
		}
	}
}