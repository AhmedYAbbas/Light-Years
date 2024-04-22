#pragma once

#include <SFML/Graphics.hpp>

#include "Weapon/BulletShooter.h"

namespace ly
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float cooldownTime = 0.3f, const sf::Vector2f& localOffset = {0.f, 0.f});

	private:
		virtual void ShootImpl() override;

	private:
		BulletShooter m_LeftShooter;
		BulletShooter m_MidShooter;
		BulletShooter m_RightShooter;
	};
}