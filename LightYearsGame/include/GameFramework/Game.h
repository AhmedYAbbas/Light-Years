#pragma once

#include <LightYears.h>

namespace ly
{
	class PlayerSpaceship;
	class Spaceship;

	class Game : public Application
	{
	public:
		Game();

		virtual void Render() override;
		virtual void Tick(float deltaTime) override;

	private:
		float counter = 0.f;
		WeakRef<PlayerSpaceship> playerSpaceship;
		WeakRef<Spaceship> test;
	};
}