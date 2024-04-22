#include "Player/Reward.h"
#include "Player/PlayerSpaceship.h"
#include "Weapon/ThreeWayShooter.h"
#include "Weapon/FrontalWiper.h"

namespace ly
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, float speed)
		: Actor{world, texturePath},
		m_Speed{speed},
		m_RewardFunc{rewardFunc}
	{
	}

	void Reward::OnActorBeginOverlap(Actor* other)
	{
		PlayerSpaceship* playerSpaceship = dynamic_cast<PlayerSpaceship*>(other);
		if (playerSpaceship && !playerSpaceship->IsPendingDestroy())
		{
			m_RewardFunc(playerSpaceship);
			Destroy();
		}
	}

	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}

	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset({0.f, m_Speed * deltaTime});
	}

	WeakRef<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth);
	}

	WeakRef<Reward> CreateThreeWayShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreeWayShooter);
	}

	WeakRef<Reward> CreateFrontalWiperShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontalWiperShooter);
	}

	WeakRef<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc)
	{
		return world->SpawnActor<Reward>(texturePath, rewardFunc);
	}

	void RewardHealth(PlayerSpaceship* player)
	{
		static float health = 10.f;
		if (player && !player->IsPendingDestroy())
			player->GetHealthComponent().ChangeHealth(10.f);
	}

	void RewardThreeWayShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
			player->SetShooter(CreateScope<ThreeWayShooter>(player, 0.4f, sf::Vector2f{50.f, 0.f}));
	}

	void RewardFrontalWiperShooter(PlayerSpaceship* player)
	{
		if (player && !player->IsPendingDestroy())
			player->SetShooter(CreateScope<FrontalWiper>(player, 0.4f, sf::Vector2f {50.f, 0.f}));
	}
}