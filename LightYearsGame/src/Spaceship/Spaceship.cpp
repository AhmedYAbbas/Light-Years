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

		m_HealthComponent.onHealthChanged.Bind(GetWeakRef(), &Spaceship::OnHealthChanged);
		m_HealthComponent.onTakenDamage.Bind(GetWeakRef(), &Spaceship::OnTakenDamage);
		m_HealthComponent.onHealthEmpty.Bind(GetWeakRef(), &Spaceship::Blow);
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
	{
	}

	void Spaceship::OnTakenDamage(float amount, float health, float maxHealth)
	{
	}

	void Spaceship::Blow()
	{
		Destroy();
	}

	void Spaceship::SetVelocity(const sf::Vector2f& velocity)
	{
		m_Velocity = velocity;
	}

	void Spaceship::Shoot()
	{
	}

	void Spaceship::TakeDamage(float amount)
	{
		m_HealthComponent.ChangeHealth(-amount);
	}
}
