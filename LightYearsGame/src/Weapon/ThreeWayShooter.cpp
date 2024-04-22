#include "Weapon/ThreeWayShooter.h"

namespace ly
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
		: Shooter{owner},
		m_LeftShooter{owner, cooldownTime, localOffset + sf::Vector2f{10.f, -10.f}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		m_MidShooter{owner, cooldownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		m_RightShooter{owner, cooldownTime, localOffset + sf::Vector2f{10.f, 10.f}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
	{
	}

	void ThreeWayShooter::ShootImpl()
	{
		m_LeftShooter.Shoot();
		m_MidShooter.Shoot();
		m_RightShooter.Shoot();
	}
}