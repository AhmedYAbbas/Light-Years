#include <Utility/Math.h>

#include "Enemy/EnemySpaceship.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* world, const std::string& texturePath, float collisionDamage, Vector<RewardFactoryFunc> rewards)
		: Spaceship {world, texturePath}, m_CollisionDamage {collisionDamage}, m_RewardFactories{rewards}
	{
		SetTeamID(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f))
			Destroy();
	}

	void EnemySpaceship::OnActorBeginOverlap(Actor* other)
	{
		Spaceship::OnActorBeginOverlap(other);
		if (IsOtherHostile(other))
			other->TakeDamage(m_CollisionDamage);
	}

	void EnemySpaceship::PreDestruction()
	{
		SpawnReward();
	}

	void EnemySpaceship::SpawnReward()
	{
		if (m_RewardFactories.empty())
			return;

		int pick = Math::RandomRange(0, m_RewardFactories.size() - 1);
		if (pick >= 0 && pick < m_RewardFactories.size())
		{
			WeakRef<Reward> reward = m_RewardFactories[pick](GetWorld());
			reward.lock()->SetActorLocation(GetActorLocation());
		}
	}
}