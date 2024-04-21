#include "Enemy/EnemySpaceship.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* world, const std::string& texturePath, float collisionDamage)
		: Spaceship{world, texturePath}, m_CollisionDamage{collisionDamage}
	{
		SetTeamID(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width))
			Destroy();
	}

	void EnemySpaceship::OnActorBeginOverlap(Actor* other)
	{
		Spaceship::OnActorBeginOverlap(other);
		if (IsOtherHostile(other))
			other->TakeDamage(m_CollisionDamage);
	}
}