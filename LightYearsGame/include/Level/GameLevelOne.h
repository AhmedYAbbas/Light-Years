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
		WeakRef<PlayerSpaceship> playerSpaceship;
	};
}