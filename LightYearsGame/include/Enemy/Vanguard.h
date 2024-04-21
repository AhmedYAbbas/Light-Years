#pragma once

#include "Enemy/EnemySpaceship.h"

namespace ly
{
	class BulletShooter;

	class Vanguard : public EnemySpaceship
	{
	public:
		Vanguard(World* world, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png", const sf::Vector2f velocity = {0.f, 50.f});

		virtual void Shoot() override;

	protected:
		virtual void Tick(float deltaTime) override;

	private:
		Scope<BulletShooter> m_Shooter;
	};
}