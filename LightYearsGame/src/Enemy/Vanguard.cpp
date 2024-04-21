#include "Enemy/Vanguard.h"

namespace ly
{
	Vanguard::Vanguard(World* world, const std::string& texturePath, const sf::Vector2f velocity)
		: EnemySpaceship{world, texturePath}, m_Shooter{CreateScope<BulletShooter>(this, 1.f, sf::Vector2f{50.f, 0.f})}
	{
		SetVelocity(velocity);
		SetActorRotation(180.f);
	}

	void Vanguard::Shoot()
	{
		m_Shooter->Shoot();
	}

	void Vanguard::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}
}