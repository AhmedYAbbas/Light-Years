#pragma once

#include <SFML/Graphics.hpp>
#include <Gameplay/GameStage.h>
#include <Framework/TimerManager.h>

namespace ly
{
	class HexagonStage : public GameStage
	{
	public:
		HexagonStage(World* world);
		virtual void StartStage() override;

	private:
		virtual void StageFinished() override;
		void SpawnHexagon();

	private:
		float m_SpawnInterval;
		float m_SideSpawnOffset;
		
		int m_SpawnGroupAmount;
		int m_CurrentSpawnCount;

		sf::Vector2f m_MidSpawnLoc;
		sf::Vector2f m_LeftSpawnLoc;
		sf::Vector2f m_RightSpawnLoc;

		TimerHandle m_SpawnTimer;
	};
}