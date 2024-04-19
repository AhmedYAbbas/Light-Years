#include <Core/Core.h>
#include <Framework/World.h>

#include "Weapon/BulletShooter.h"
#include "Weapon/Bullet.h"


namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime)
	: Shooter {owner}, m_CooldownClock {}, m_CooldownTime{cooldownTime}
	{
	}

	bool BulletShooter::IsOnCooldown() const
	{
		if (m_CooldownClock.getElapsedTime().asSeconds() > m_CooldownTime)
			return false;

		return true;
	}

	void BulletShooter::ShootImpl()
	{
		m_CooldownClock.restart();
		WeakRef<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation());
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation());
	}
}
