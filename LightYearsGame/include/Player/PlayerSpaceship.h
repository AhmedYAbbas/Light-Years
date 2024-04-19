#pragma once

#include "Spaceship/Spaceship.h"
#include "Weapon/BulletShooter.h"

namespace ly
{
	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* world, const std::string& filepath = "SpaceShooterRedux/PNG/playerShip1_blue.png");

		virtual void Tick(float deltaTime) override;
		inline void SetSpeed(float speed) { m_Speed = speed; }
		inline float GetSpeed() const { return m_Speed; }
		virtual void Shoot() override;

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void NormalizeInput();
		void ClampInputToScreenEdge();

	private:
		sf::Vector2f m_MoveInput;
		float m_Speed;
		Scope<BulletShooter> m_Shooter;
	};
}