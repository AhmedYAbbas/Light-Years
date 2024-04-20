#pragma once

#include <Framework/Actor.h>
#include "Gameplay/HealthComponent.h"

namespace ly
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* world, const std::string& filepath = "");

		void SetVelocity(const sf::Vector2f& velocity);
		inline const sf::Vector2f& GetVelocity() const { return m_Velocity; }

		virtual void Shoot();
		virtual void TakeDamage(float amount) override;

	protected:
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnHealthChanged(float amount, float health, float maxHealth);
		virtual void OnTakenDamage(float amount, float health, float maxHealth);
		virtual void Blow();

		void Blink();
		void UpdateBlink(float deltaTime);

	private:
		sf::Vector2f m_Velocity;
		HealthComponent m_HealthComponent;

		float m_BlinkTime;
		float m_BlinkDuration;
		sf::Color m_BlinkColorOffset;
	};
}