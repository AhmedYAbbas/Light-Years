#include <Utility/Math.h>

#include "Enemy/EnemySpaceship.h"
#include "Player/Player.h"
#include "Player/PlayerManager.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* world, const std::string& texturePath, float collisionDamage, float rewardSpawnWeight, Vector<RewardFactoryFunc> rewards)
		: Spaceship{world, texturePath}, m_CollisionDamage{collisionDamage}, m_ScoreAwardAmount{10}, m_RewardSpawnWeight{rewardSpawnWeight}, m_RewardFactories{rewards}
	{
		SetTeamID(2);
	}

	void EnemySpaceship::SetRewardSpawnWeight(float weight)
	{
		if (weight < 0 || weight > 1)
			return;

		m_RewardSpawnWeight = weight;
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
		if (Player* player = PlayerManager::Get().GetPlayer())
			player->AddScore(m_ScoreAwardAmount);
	}

	void EnemySpaceship::SpawnReward()
	{
		if (m_RewardFactories.empty())
			return;

		if (m_RewardSpawnWeight < Math::RandomRange(0.f, 1.f))
			return;

		int pick = Math::RandomRange(0, m_RewardFactories.size() - 1);
		if (pick >= 0 && pick < m_RewardFactories.size())
		{
			WeakRef<Reward> reward = m_RewardFactories[pick](GetWorld());
			reward.lock()->SetActorLocation(GetActorLocation());
		}
	}
}