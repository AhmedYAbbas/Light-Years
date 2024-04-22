#include "Weapon/Shooter.h"

namespace ly
{
	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
			ShootImpl();
	}

	void Shooter::IncrementLevel(int amount)
	{
		if (m_CurrentLevel == m_MaxLevel)
			return;

		m_CurrentLevel += amount;
	}

	Shooter::Shooter(Actor* owner)
		: m_Owner{owner}, m_CurrentLevel{1}, m_MaxLevel{4}
	{
	} 
}
