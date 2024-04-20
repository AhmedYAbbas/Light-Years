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
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& velocity)
	{
		m_Velocity = velocity;
	}

	void Spaceship::Shoot()
	{
	}
}
