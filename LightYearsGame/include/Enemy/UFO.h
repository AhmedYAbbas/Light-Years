#pragma once

#include "Enemy/EnemySpaceship.h"
#include "Weapon/BulletShooter.h"

namespace ly
{
	class UFO : public EnemySpaceship
	{
	public:
		UFO(World* world, const std::string& texturePath = "SpaceShooterRedux/PNG/ufoRed.png", const sf::Vector2f& velocity = {0.f, 0.f}, float rotationSpeed = 40.f);
		virtual void Shoot() override;

	protected:
		virtual void Tick(float deltaTime) override;

	private:
		void InitializeShooters();

	private:
		float m_RotationSpeed;
		Vector<Ref<BulletShooter>> m_Shooters;
	};
}