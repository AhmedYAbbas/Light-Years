#pragma once

#include <functional>
#include <Framework/Actor.h>

namespace ly
{
	class PlayerSpaceship;
	class Reward;
	using RewardFactoryFunc = std::function<WeakRef<Reward>(World*)>;
	using RewardFunc = std::function<void(PlayerSpaceship*)>;

	class Reward : public Actor
	{
	public:
		Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed = 200.f);

	protected:
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;

	private:
		float m_Speed;
		RewardFunc m_RewardFunc;
	};

	WeakRef<Reward> CreateHealthReward(World* world);
	WeakRef<Reward> CreateThreeWayShooterReward(World* world);
	WeakRef<Reward> CreateFrontalWiperShooterReward(World* world);

	WeakRef<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc);

	void RewardHealth(PlayerSpaceship* player);
	void RewardThreeWayShooter(PlayerSpaceship* player);
	void RewardFrontalWiperShooter(PlayerSpaceship* player);
}