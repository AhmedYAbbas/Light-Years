#pragma once

#include "Gameplay/GameStage.h"

namespace ly
{
	class WaitStage : public GameStage
	{
	public:
		WaitStage(World* world, float waitDuration = 5.f);
		virtual void StartStage() override;
		virtual void StageFinished() override;

	private:
		float m_WaitDuration;
	};
}