#include "Spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* world, const std::string& filepath)
		: Actor {world, filepath}, m_Velocity{}, m_HealthComponent{100.f, 100.f}
	{
	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
		//m_HealthComponent.onHealthChanged.Bind(GetWeakRef(), &Spaceship::OnHealthChanged);
		//m_HealthComponent.onHealthChanged.Broadcast(11, 98, 100);
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
	{
		LOG("Health Changed by: % f, now health is : % f / % f", amount, health, maxHealth);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& velocity)
	{
		m_Velocity = velocity;
	}

	void Spaceship::Shoot()
	{
	}
}
