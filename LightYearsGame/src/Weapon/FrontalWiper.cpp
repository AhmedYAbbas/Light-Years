#include "Weapon/FrontalWiper.h"

namespace ly
{
	FrontalWiper::FrontalWiper(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset, float width)
		: Shooter{owner},
		m_Width{width},
		m_Shooter1{owner, cooldownTime, {localOffset.x, localOffset.y - width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
		m_Shooter2{owner, cooldownTime, {localOffset.x, localOffset.y - width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
		m_Shooter3{owner, cooldownTime, {localOffset.x, localOffset.y + width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"},
		m_Shooter4{owner, cooldownTime, {localOffset.x, localOffset.y + width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
		m_Shooter5{owner, cooldownTime / 1.5f, {localOffset.x, localOffset.y + width / 1.5f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
		m_Shooter6{owner, cooldownTime / 1.5f, {localOffset.x, localOffset.y - width / 1.5f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"}
	{
	}

	void FrontalWiper::IncrementLevel(int amount)
	{
		Shooter::IncrementLevel(amount);

		m_Shooter1.IncrementLevel(amount);
		m_Shooter2.IncrementLevel(amount);
		m_Shooter3.IncrementLevel(amount);
		m_Shooter4.IncrementLevel(amount);
		m_Shooter5.IncrementLevel(amount);
		m_Shooter6.IncrementLevel(amount);
	}

	void FrontalWiper::SetCurrentLevel(int level)
	{
		Shooter::SetCurrentLevel(level);

		m_Shooter1.SetCurrentLevel(level);
		m_Shooter2.SetCurrentLevel(level);
		m_Shooter3.SetCurrentLevel(level);
		m_Shooter4.SetCurrentLevel(level);
		m_Shooter5.SetCurrentLevel(level);
		m_Shooter6.SetCurrentLevel(level);
	}

	void FrontalWiper::ShootImpl()
	{
		m_Shooter1.Shoot();
		m_Shooter2.Shoot();
		m_Shooter3.Shoot();
		m_Shooter4.Shoot();

		if (GetCurrentLevel() == GetMaxLevel())
		{
			m_Shooter5.Shoot();
			m_Shooter6.Shoot();
		}
	}
}