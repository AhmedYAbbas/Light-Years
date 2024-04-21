#include <Framework/World.h>

#include "Enemy/HexagonStage.h"
#include "Enemy/Hexagon.h"

namespace ly
{
	HexagonStage::HexagonStage(World* world)
		: GameStage{world},
		m_SpawnInterval{5.f},
		m_SideSpawnOffset{80.f},
		m_SpawnGroupAmount{5},
		m_CurrentSpawnCount{0},
		m_MidSpawnLoc{world->GetWindowSize().x / 2.f, -100.f},
		m_LeftSpawnLoc{world->GetWindowSize().x / 2.f - m_SideSpawnOffset, -100.f - m_SideSpawnOffset},
		m_RightSpawnLoc{world->GetWindowSize().x / 2.f + m_SideSpawnOffset, -100.f - m_SideSpawnOffset}
	{
	}

	void HexagonStage::StartStage()
	{
		GameStage::StartStage();
		m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &HexagonStage::SpawnHexagon, m_SpawnInterval, true);
	}

	void HexagonStage::StageFinished()
	{
		GameStage::StageFinished();
		TimerManager::Get().ClearTimer(m_SpawnTimer);
	}

	void HexagonStage::SpawnHexagon()
	{
		WeakRef<Hexagon> hexagon = GetWorld()->SpawnActor<Hexagon>();

		hexagon.lock()->SetActorLocation(m_MidSpawnLoc);
		hexagon = GetWorld()->SpawnActor<Hexagon>();
		hexagon.lock()->SetActorLocation(m_LeftSpawnLoc);
		hexagon = GetWorld()->SpawnActor<Hexagon>();
		hexagon.lock()->SetActorLocation(m_RightSpawnLoc);

		if (++m_CurrentSpawnCount == m_SpawnGroupAmount)
			FinishStage();
	}
}