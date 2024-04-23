#pragma once

#include <SFML/Graphics.hpp>
#include <Gameplay/GameStage.h>
#include <Framework/TimerManager.h>

namespace ly
{
	class ChaosStage : public GameStage
	{
	public:
		ChaosStage(World* world);

		virtual void StartStage() override;
		virtual void StageFinished() override;

	private:
		void SpawnVanguard();
		void SpawnTwinBlade();
		void SpawnHexagon();
		void SpawnUFO();

		void IncreaseDifficulty();
		void StageDurationReached();

		sf::Vector2f GetRandomSpawnLocationTop() const;
		sf::Vector2f GetRandomSpawnLocationSide() const;

	private:
		float m_SpawnInterval;
		float m_MinSpawnInterval;

		float m_SpawnIntervalDecrement;
		float m_SpawnIntervalDecrementInterval;

		float m_StageDuration;

		TimerHandle m_DifficultyTimerHandle;
		TimerHandle m_SpawnTimer;
	};
}