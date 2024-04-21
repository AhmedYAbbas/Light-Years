#pragma once

#include <SFML/Graphics.hpp>
#include <Gameplay/GameStage.h>
#include <Framework/TimerManager.h>

#include "Gameplay/GameStage.h"

namespace ly
{
	class TwinBladeStage : public GameStage
	{
	public:
		TwinBladeStage(World* world);
		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnTwinBlade();

	private:
		float m_SpawnInterval;
		float m_SwitchInterval;
		float m_SpawnDistanceToCenter;

		sf::Vector2f m_LeftSpawnLoc;
		sf::Vector2f m_RightSpawnLoc;
		sf::Vector2f m_SpawnLoc;

		TimerHandle m_SpawnTimerHandle;

		int m_SpawnAmount;
		int m_CurrentSpawnCount;
	};
}