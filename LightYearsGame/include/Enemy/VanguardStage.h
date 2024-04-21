#pragma once

#include <SFML/Graphics.hpp>
#include <Gameplay/GameStage.h>
#include <Framework/TimerManager.h>

namespace ly
{
	class VanguardStage : public GameStage
	{
	public:
		VanguardStage(World* world);

		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;

		void SpawnVangurad();
		void SwitchRow();

	private:
		float m_SpawnInterval;
		float m_SwitchInterval;
		float m_SpawnDistanceToEdge;

		sf::Vector2f m_LeftSpawnLoc;
		sf::Vector2f m_RightSpawnLoc;
		sf::Vector2f m_SpawnLoc;

		TimerHandle m_SpawnTimerHandle;
		TimerHandle m_SwitchTimerHandle;

		int m_RowsToSpawn;
		int m_RowSpawnCount;

		int m_VanguardsPerRow;
		int m_CurrentRowVanguardCount;
	};
}