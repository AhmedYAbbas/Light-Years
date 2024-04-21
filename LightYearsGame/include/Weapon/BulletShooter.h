#pragma once

#include <SFML/System.hpp>
#include "Weapon/Shooter.h"

namespace ly
{
	class BulletShooter : public Shooter
	{
	public:
		BulletShooter(Actor* owner, float cooldownTime = 1.f, const sf::Vector2f& localPositionOffset = sf::Vector2f{0.f, 0.f}, float localRotationOffset = 0.f);

		virtual bool IsOnCooldown() const override;

	private:
		virtual void ShootImpl() override;

	private:
		sf::Clock m_CooldownClock;
		float m_CooldownTime;
		sf::Vector2f m_LocalPositionOffset;
		float m_LocalRotationOffset;
	};
}