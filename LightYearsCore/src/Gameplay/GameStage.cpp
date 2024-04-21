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
	}

	void GameStage::FinishStage()
	{
		m_StageFinished = true;
		OnStageFinished.Broadcast();
		StageFinished();
	}

	void GameStage::StageFinished()
	{
		LOG("Stage Finished!");
	}
}