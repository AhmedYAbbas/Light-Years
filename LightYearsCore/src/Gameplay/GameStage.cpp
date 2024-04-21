#include "Gameplay/GameStage.h"
#include "Core/Core.h"

namespace ly
{
	GameStage::GameStage(World* world)
		: m_World{world}, m_StageFinished{false}
	{
	}

	void GameStage::StartStage()
	{
		LOG("Stage Started!");
	}

	void GameStage::TickStage(float deltaTime)
	{
		LOG("Stage Ticking!");
	}

	void GameStage::FinishStage()
	{
		m_StageFinished = ture;
		OnStageFinished.Broadcast();
		StageFinished();
	}

	GameStage::StageFinished()
	{
		LOG("Stage Finished!");
	}
}