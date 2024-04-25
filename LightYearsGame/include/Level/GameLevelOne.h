#pragma once

#include <Framework/TimerManager.h>

#include "Framework/World.h"

namespace ly
{
	class PlayerSpaceship;
	class GameplayHUD;
	class TimerHandle;

	class GameLevelOne : public World
	{
	public:
		GameLevelOne();

	private:
		virtual void BeginPlay() override;
		virtual void InitGameStages() override;
		virtual void AllGameStagesFinished() override;

		void OnPlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);
		void GameOver();

		void Quit();
		void Restart();

	private:
		WeakRef<PlayerSpaceship> m_PlayerSpaceship;
		WeakRef<GameplayHUD> m_GameplayHUD;
		TimerHandle m_TimerHandle;
	};
}