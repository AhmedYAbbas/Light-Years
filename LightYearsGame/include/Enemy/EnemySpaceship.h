#pragma once

#include "Spaceship/Spaceship.h"
#include "Player/Reward.h"

namespace ly
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* world,
			const std::string& texturePath,
			float collisionDamage = 200.f,
			float rewardSpawnWeight = 0.5f,
			Vector<RewardFactoryFunc> rewards = 
			{
				CreateHealthReward,
				CreateThreeWayShooterReward,
				CreateFrontalWiperShooterReward,
				CreateLifeReward
			}
		);

		inline void SetScoreAwardAmount(int amount) { m_ScoreAwardAmount = amount; }
		void SetRewardSpawnWeight(float weight);

	protected:
		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;
		virtual void PreDestruction() override;

		void SpawnReward();

	private:
		float m_CollisionDamage;
		int m_ScoreAwardAmount;
		float m_RewardSpawnWeight;
		Vector<RewardFactoryFunc> m_RewardFactories;
	};
}