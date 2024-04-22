#pragma once

#include <Framework/TimerManager.h>

#include "Framework/World.h"

namespace ly
{
	class PlayerSpaceship;
	class TimerHandle;

	class GameLevelOne : public World
	{
	public:
		GameLevelOne();

	private:
		virtual void BeginPlay() override;
		virtual void InitGameStages() override;

		void OnPlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);
		void GameOver();

	private:
		WeakRef<PlayerSpaceship> m_PlayerSpaceship;
		TimerHandle m_TimerHandle;
	};
}