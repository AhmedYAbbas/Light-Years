#include <Framework/World.h>

#include "Enemy/VanguardStage.h"
#include "Enemy/Vanguard.h"

namespace ly
{
	VanguardStage::VanguardStage(World* world)
		: GameStage{world},
		m_SpawnInterval{1.5f},
		m_SwitchInterval{5.f},
		m_SpawnDistanceToEdge{100.f},
		m_LeftSpawnLoc{0.f, 0.f},
		m_RightSpawnLoc{0.f, 0.f},
		m_SpawnLoc{0.f, 0.f},
		m_RowsToSpawn{2},
		m_RowSpawnCount{0},
		m_VanguardsPerRow{5},
		m_CurrentRowVanguardCount{0}
	{
	}

	void VanguardStage::StartStage()
	{
		GameStage::StartStage();

		sf::Vector2u windowSize = GetWorld()->GetWindowSize();
		m_LeftSpawnLoc = sf::Vector2f {m_SpawnDistanceToEdge, -100.f};
		m_RightSpawnLoc = sf::Vector2f {windowSize.x - m_SpawnDistanceToEdge, -100.f};

		SwitchRow();
	}

	void VanguardStage::StageFinished()
	{
		GameStage::StageFinished();

		TimerManager::Get().ClearTimer(m_SpawnTimerHandle);
		TimerManager::Get().ClearTimer(m_SwitchTimerHandle);
	}

	void VanguardStage::SpawnVangurad()
	{
		WeakRef<Vanguard> vanguard = GetWorld()->SpawnActor<Vanguard>();
		vanguard.lock()->SetActorLocation(m_SpawnLoc);
		if (++m_CurrentRowVanguardCount == m_VanguardsPerRow)
		{
			TimerManager::Get().ClearTimer(m_SpawnTimerHandle);
			m_SwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, m_SwitchInterval, false);
			m_CurrentRowVanguardCount = 0;
		}
	}

	void VanguardStage::SwitchRow()
	{
		if (m_RowSpawnCount == m_RowsToSpawn)
		{
			FinishStage();
			return;
		}

		if (m_SpawnLoc == m_LeftSpawnLoc)
			m_SpawnLoc = m_RightSpawnLoc;
		else
			m_SpawnLoc = m_LeftSpawnLoc;

		m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVangurad, m_SpawnInterval, true);
		++m_RowSpawnCount;
	}
}