#include "Gameplay/WaitStage.h"
#include "Framework/TimerManager.h"

namespace ly
{
	WaitStage::WaitStage(World* world, float waitDuration)
		: GameStage{world}, m_WaitDuration{waitDuration}
	{
	}

	void WaitStage::StartStage()
	{
		GameStage::StartStage();

		TimerManager::Get().SetTimer(GetWeakRef(), &WaitStage::FinishStage, m_WaitDuration);
	}

	void WaitStage::StageFinished()
	{
		GameStage::StageFinished();
	}
}