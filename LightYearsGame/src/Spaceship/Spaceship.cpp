#include <Utility/Math.h>

#include "Spaceship/Spaceship.h"
#include "VFX/Explosion.h"

namespace ly
{
	Spaceship::Spaceship(World* world, const std::string& filepath)
		: Actor {world, filepath}, m_Velocity{}, m_HealthComponent{100.f, 100.f}, m_BlinkTime{0.f}, m_BlinkDuration{0.2f}, m_BlinkColorOffset{255, 0, 0}
	{
	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);

		m_HealthComponent.OnHealthChanged.Bind(GetWeakRef(), &Spaceship::OnHealthChanged);
		m_HealthComponent.OnTakenDamage.Bind(GetWeakRef(), &Spaceship::OnTakenDamage);
		m_HealthComponent.OnHealthEmpty.Bind(GetWeakRef(), &Spaceship::Blow);
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);
	}

	void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
	{
	}

	void Spaceship::OnTakenDamage(float amount, float health, float maxHealth)
	{
		Blink();
	}

	void Spaceship::Blow()
	{
		Scope<Explosion> explosion = CreateScope<Explosion>();
		explosion->SpawnExplosion(GetWorld(), GetActorLocation());
		PreDestruction();
		Destroy();
	}

	void Spaceship::PreDestruction()
	{
	}

	void Spaceship::Blink()
	{
		if (m_BlinkTime <= 0.f)
			m_BlinkTime = m_BlinkDuration;
	}

	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (m_BlinkTime > 0.f)
		{
			m_BlinkTime -= deltaTime; 
			m_BlinkTime = m_BlinkTime > 0.f ? m_BlinkTime : 0.f;
			GetSprite().setColor(Math::Lerp(sf::Color::White, m_BlinkColorOffset, m_BlinkTime));
		}

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
