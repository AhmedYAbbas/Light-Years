#include "Enemy/Vanguard.h"
#include "Weapon/BulletShooter.h"

namespace ly
{
	Vanguard::Vanguard(World* world, const std::string& texturePath, const sf::Vector2f velocity)
		: EnemySpaceship{world, texturePath}, m_Shooter{CreateScope<BulletShooter>(this)}
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