#pragma once

#include <Gameplay/GameStage.h>

namespace ly
{
	class Actor;

	class BossStage : public GameStage
	{
	public:
		BossStage(World* world);

		virtual void StartStage() override;

	private:
		void OnBossDestroyed(Actor* destroyedBoss);
	};
}