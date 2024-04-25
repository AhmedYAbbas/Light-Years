#include <Framework/World.h>

#include "Enemy/BossStage.h"
#include "Enemy/Boss.h"

namespace ly
{
	BossStage::BossStage(World* world)
		: GameStage{world}
	{
	}

	void BossStage::StartStage()
	{
		WeakRef<Boss> boss = GetWorld()->SpawnActor<Boss>();
		const auto windowSize = GetWorld()->GetWindowSize();
		boss.lock()->SetActorLocation({windowSize.x / 2.f, 200.f});
		boss.lock()->OnActorDestroyed.Bind(GetWeakRef(), &BossStage::OnBossDestroyed);
	}

	void BossStage::OnBossDestroyed(Actor* destroyedBoss)
	{
 		FinishStage();
	}
}