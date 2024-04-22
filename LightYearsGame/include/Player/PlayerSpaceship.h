#pragma once

#include "Spaceship/Spaceship.h"
#include "Weapon/Shooter.h"

namespace ly
{
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* world, const std::string& filepath = "SpaceShooterRedux/PNG/playerShip1_blue.png");

		virtual void Tick(float deltaTime) override;
		virtual void Shoot() override;

		inline void SetSpeed(float speed) { m_Speed = speed; }
		inline float GetSpeed() const { return m_Speed; }
		inline void SetShooter(Scope<Shooter> shooter) { m_Shooter = std::move(shooter); }

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void NormalizeInput();
		void ClampInputToScreenEdge();

	private:
		sf::Vector2f m_MoveInput;
		float m_Speed;
		Scope<Shooter> m_Shooter;
	};
}