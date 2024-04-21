#include "Enemy/TwinBlade.h"

namespace ly
{
	TwinBlade::TwinBlade(World* world, const std::string& texturePath, const sf::Vector2f velocity)
		: EnemySpaceship{world, texturePath},
		m_LeftShooter{CreateScope<BulletShooter>(this, 1.f, sf::Vector2f{50.f, -20.f})},
		m_RightShooter{CreateScope<BulletShooter>(this, 1.f, sf::Vector2f{50.f, 20.f})}
	{
		SetVelocity(velocity);
		SetActorRotation(180.f);
	}

	void TwinBlade::Shoot()
	{
		m_LeftShooter->Shoot();
		m_RightShooter->Shoot();
	}

	void TwinBlade::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		Shoot();
	}
}