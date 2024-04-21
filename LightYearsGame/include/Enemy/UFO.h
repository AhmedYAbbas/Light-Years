#pragma once

#include "Enemy/EnemySpaceship.h"
#include "Weapon/BulletShooter.h"

namespace ly
{
	class UFO : public EnemySpaceship
	{
	public:
		UFO(World* world, const sf::Vector2f& velocity, const std::string& texturePath = "SpaceShooterRedux/PNG/ufoRed.png", float rotationSpeed = 40.f);
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