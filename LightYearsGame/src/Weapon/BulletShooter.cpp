#include <Core/Core.h>
#include <Framework/World.h>

#include "Weapon/BulletShooter.h"
#include "Weapon/Bullet.h"


namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localPositionOffset, float localRotationOffset)
	: Shooter {owner}, m_CooldownClock {}, m_CooldownTime{cooldownTime}, m_LocalPositionOffset{localPositionOffset}, m_LocalRotationOffset{localRotationOffset}
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
		sf::Vector2f ownerForwardDirection = GetOwner()->GetForwardDirection();
		sf::Vector2f ownerRightDirection = GetOwner()->GetRightDirection();

		m_CooldownClock.restart();
		WeakRef<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");

		// Forward is +ve X(right), Right is +ve Y(downwards)
		newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + -ownerRightDirection * m_LocalPositionOffset.x + ownerForwardDirection * m_LocalPositionOffset.y);
		newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + m_LocalRotationOffset);
	}
}
