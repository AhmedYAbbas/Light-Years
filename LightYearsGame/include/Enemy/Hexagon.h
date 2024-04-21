#pragma once

#include "Enemy/EnemySpaceship.h"
#include "Weapon/BulletShooter.h"

namespace ly
{
	class World;

	class Hexagon : public EnemySpaceship
	{
	public:
		Hexagon(World* world, const std::string& texturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen4.png", const sf::Vector2f& velocity = {0.f, 100.f});
		virtual void Shoot() override;

	protected:
		virtual void Tick(float deltaTime) override;

	private:
		void InitializeShooters();

	private:
		Vector<Scope<BulletShooter>> m_Shooters;
	};
}