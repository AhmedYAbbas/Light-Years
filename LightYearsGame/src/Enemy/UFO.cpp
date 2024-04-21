#include <Framework/World.h>
#include "Enemy/UFO.h"

namespace ly
{
	UFO::UFO(World* world, const std::string& texturePath, const sf::Vector2f& velocity, float rotationSpeed)
		: EnemySpaceship{world, texturePath}, m_RotationSpeed{rotationSpeed}
	{
		SetVelocity(velocity);
		SetActorRotation(180.f);
		InitializeShooters();
	}

	void UFO::Shoot()
	{
		for (auto& shooter : m_Shooters)
			shooter->Shoot();
	}

	void UFO::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
		AddActorRotationOffset(m_RotationSpeed * deltaTime);
	}

	void UFO::InitializeShooters()
	{
		m_Shooters.push_back(CreateScope<BulletShooter>(this, 1.f, sf::Vector2f {0.f, 0.f}, -60.f));
		m_Shooters.push_back(CreateScope<BulletShooter>(this, 1.f, sf::Vector2f {0.f, 0.f}, 60.f));
		m_Shooters.push_back(CreateScope<BulletShooter>(this, 1.f, sf::Vector2f {0.f, 0.f}, 180.f));
	}
}