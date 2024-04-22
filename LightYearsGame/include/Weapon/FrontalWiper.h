#pragma once

#include <SFML/Graphics.hpp>

#include "Weapon/BulletShooter.h"

namespace ly
{
	class FrontalWiper : public Shooter
	{
	public:
		FrontalWiper(Actor* owner, float cooldownTime = 0.3f, const sf::Vector2f& localOffset = {0.f, 0.f}, float width = 60.f);

	private:
		virtual void ShootImpl() override;

	private:
		float m_Width;

		BulletShooter m_Shooter1;
		BulletShooter m_Shooter2;
		BulletShooter m_Shooter3;
		BulletShooter m_Shooter4;
	};
}