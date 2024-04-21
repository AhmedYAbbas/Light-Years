#pragma once

#include <SFML/Graphics.hpp>
#include <Gameplay/GameStage.h>
#include <Framework/TimerManager.h>

namespace ly
{
	class UFOStage : public GameStage
	{
	public:
		UFOStage(World* world);
		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnUFO();
		sf::Vector2f GetRandomSpawnLocation() const;

	private:
		float m_SpawnInterval;
		int m_SpawnAmout;
		int m_CurrentSpawnAmout;
		float m_UFOSpeed;

		TimerHandle m_SpawnTimer;
	};
}