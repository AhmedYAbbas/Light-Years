#include <Framework/World.h>
#include "Enemy/Hexagon.h"

namespace ly
{
	Hexagon::Hexagon(World* world, const std::string& texturePath, const sf::Vector2f& velocity)
		: EnemySpaceship {world, texturePath}, m_Shooters{}
	{
		SetVelocity(velocity);
		SetActorRotation(180.f);
		InitializeShooters();
	}

	void Hexagon::Shoot()
	{
		for (auto& shooter : m_Shooters)
			shooter->Shoot();
	}

	void Hexagon::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}

	void ly::Hexagon::InitializeShooters()
	{
		m_Shooters.push_back(CreateScope<BulletShooter>(this, 1.f, sf::Vector2f {20.f, 50.f}, 30.f));
		m_Shooters.push_back(CreateScope<BulletShooter>(this, 1.f, sf::Vector2f {20.f, -50.f}, -30.f));
		m_Shooters.push_back(CreateScope<BulletShooter>(this, 1.f, sf::Vector2f {50.f, 0.f}));
		m_Shooters.push_back(CreateScope<BulletShooter>(this, 1.f, sf::Vector2f {-50.f, 0.f}, -180.f));
		m_Shooters.push_back(CreateScope<BulletShooter>(this, 1.f, sf::Vector2f {-20.f, 50.f}, 120.f));
		m_Shooters.push_back(CreateScope<BulletShooter>(this, 1.f, sf::Vector2f {-20.f, -50.f}, -120.f));
	}
}
