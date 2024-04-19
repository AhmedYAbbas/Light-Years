#include "Weapon/Shooter.h"

namespace ly
{
	void Shooter::Shoot()
	{
		if (CanShoot() && !IsOnCooldown())
			ShootImpl();
	}

	Shooter::Shooter(Actor* owner)
		: m_Owner{owner}
	{
	} 
}
