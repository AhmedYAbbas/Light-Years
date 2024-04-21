#include <Framework/World.h>

#include "Enemy/TwinBladeStage.h"
#include "Enemy/TwinBlade.h"

namespace ly
{
    TwinBladeStage::TwinBladeStage(World* world)
        : GameStage{world},
        m_SpawnInterval{1.5f},
        m_SpawnDistanceToCenter{100.f},
        m_LeftSpawnLoc{world->GetWindowSize().x / 2.f - m_SpawnDistanceToCenter, -100.f},
        m_RightSpawnLoc{world->GetWindowSize().x / 2.f + m_SpawnDistanceToCenter, -100.f},
        m_SpawnLoc{m_LeftSpawnLoc},
        m_SpawnAmount{10},
        m_CurrentSpawnCount{0}
    { 
    }

    void TwinBladeStage::StartStage()
    {
        GameStage::StartStage();

        m_SpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, m_SpawnInterval, true);
    }

    void TwinBladeStage::StageFinished()
    {
        GameStage::StageFinished();

        TimerManager::Get().ClearTimer(m_SpawnTimerHandle);
    }

    void TwinBladeStage::SpawnTwinBlade()
    {
        WeakRef<TwinBlade> twinBlade = GetWorld()->SpawnActor<TwinBlade>();
        twinBlade.lock()->SetActorLocation(m_SpawnLoc);
        if (m_SpawnLoc == m_LeftSpawnLoc)
            m_SpawnLoc = m_RightSpawnLoc;
        else
            m_SpawnLoc = m_LeftSpawnLoc;

        ++m_CurrentSpawnCount;
        if (m_CurrentSpawnCount == m_SpawnAmount)
        {
            m_CurrentSpawnCount = 0;
            FinishStage();
        }
    }
}