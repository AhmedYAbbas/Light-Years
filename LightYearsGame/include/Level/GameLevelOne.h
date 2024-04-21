#pragma once

#include "Framework/World.h"

namespace ly
{
	class PlayerSpaceship;

	class GameLevelOne : public World
	{
	public:
		GameLevelOne();

	private:
		virtual void BeginPlay() override;

		void TimerCallback();

	private:
		WeakRef<PlayerSpaceship> playerSpaceship;
	};
}