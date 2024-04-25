#include "Weapon/ThreeWayShooter.h"

namespace ly
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
		: Shooter{owner},
		m_LeftShooter{owner, cooldownTime, localOffset + sf::Vector2f{10.f, -10.f}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		m_MidShooter{owner, cooldownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		m_RightShooter{owner, cooldownTime, localOffset + sf::Vector2f{10.f, 10.f}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		m_TopLevelShooterLeft{owner, cooldownTime, localOffset + sf::Vector2f{10.f, 10.f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		m_TopLevelShooterRight{owner, cooldownTime, localOffset + sf::Vector2f{10.f, -10.f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
	{
	}

	void ThreeWayShooter::IncrementLevel(int amount)
	{
		Shooter::IncrementLevel(amount);

		m_LeftShooter.IncrementLevel(amount);
		m_MidShooter.IncrementLevel(amount);
		m_RightShooter.IncrementLevel(amount);

		m_TopLevelShooterLeft.IncrementLevel(amount);
		m_TopLevelShooterRight.IncrementLevel(amount);
	}

	void ThreeWayShooter::SetCurrentLevel(int level)
	{
		Shooter::SetCurrentLevel(level);

		m_LeftShooter.SetCurrentLevel(level);
		m_MidShooter.SetCurrentLevel(level);
		m_RightShooter.SetCurrentLevel(level);

		m_TopLevelShooterLeft.SetCurrentLevel(level);
		m_TopLevelShooterRight.SetCurrentLevel(level);
	}

	void ThreeWayShooter::ShootImpl()
	{
		m_LeftShooter.Shoot();
		m_MidShooter.Shoot();
		m_RightShooter.Shoot();

		if (GetCurrentLevel() == GetMaxLevel())
		{
			m_TopLevelShooterLeft.Shoot();
			m_TopLevelShooterRight.Shoot();
		}
	}
}