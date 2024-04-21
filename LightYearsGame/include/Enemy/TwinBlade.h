#pragma once

#include "Enemy/EnemySpaceship.h"
#include "Weapon/BulletShooter.h"

namespace ly
{
	class TwinBlade : public EnemySpaceship
	{
	public:
		TwinBlade(World* world, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlack1.png", const sf::Vector2f velocity = {0.f, 120.f});

		virtual void Shoot() override;

	protected:
		virtual void Tick(float deltaTime) override;

	private:
		Scope<BulletShooter> m_LeftShooter;
		Scope<BulletShooter> m_RightShooter;
	};
}