#pragma once

#include <Framework/TimerManager.h>

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
		virtual void TakeDamage(float amount) override;

		inline void SetSpeed(float speed) { m_Speed = speed; }
		inline float GetSpeed() const { return m_Speed; }
		void SetShooter(Scope<Shooter> shooter);

	protected:
		virtual void BeginPlay() override;

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void NormalizeInput();
		void ClampInputToScreenEdge();

		void StopInvulnerable();
		void UpdateInvulnerable(float deltaTime);

	private:
		sf::Vector2f m_MoveInput;
		float m_Speed;
		Scope<Shooter> m_Shooter;

		float m_InvulnerableTime;
		TimerHandle m_InvulnerableTimerHandle;
		bool m_Invulnerable;

		float m_InvulnerableFlashInterval;
		float m_InvulnerableFlashTimer;
		float m_InvulnerableFlashDirection;
	};
}