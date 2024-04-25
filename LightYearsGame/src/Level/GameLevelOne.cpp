#include <Gameplay/WaitStage.h>
#include <Framework/Application.h>
#include <Framework/BackdropActor.h>
#include <Framework/BackgroundLayer.h>

#include "Level/GameLevelOne.h"
#include "Player/PlayerSpaceship.h"
#include "Player/PlayerManager.h"
#include "Player/Player.h"

#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"
#include "Enemy/ChaosStage.h"
#include "Enemy/BossStage.h"

#include "Widget/GameplayHUD.h"

namespace ly
{
	GameLevelOne::GameLevelOne()
	{
	}

	void GameLevelOne::BeginPlay()
	{
		SpawnCosmetics();

		Player& player = PlayerManager::Get().CreateNewPlayer();
		m_PlayerSpaceship = player.SpawnSpaceship(this);
		m_PlayerSpaceship.lock()->OnActorDestroyed.Bind(GetWeakRef(), &GameLevelOne::OnPlayerSpaceshipDestroyed);

		m_GameplayHUD = SpawnHUD<GameplayHUD>();
		m_GameplayHUD.lock()->OnQuitButtonClicked.Bind(GetWeakRef(), &GameLevelOne::Quit);
		m_GameplayHUD.lock()->OnRestartButtonClicked.Bind(GetWeakRef(), &GameLevelOne::Restart);
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 5.f)});
		AddStage(Ref<VanguardStage>{CreateRef<VanguardStage>(this)});

		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 15.f)});
		AddStage(Ref<TwinBladeStage>{CreateRef<TwinBladeStage>(this)});

		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 12.f)});
		AddStage(Ref<HexagonStage>{CreateRef<HexagonStage>(this)});

		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 10.f)});
		AddStage(Ref<UFOStage>{CreateRef<UFOStage>(this)});

		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 10.f)});
		AddStage(Ref<ChaosStage>{CreateRef<ChaosStage>(this)});

		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 10.f)});
		AddStage(Ref<BossStage>{CreateRef<BossStage>(this)});

	}

	void GameLevelOne::AllGameStagesFinished()
	{
		m_GameplayHUD.lock()->GameFinished(true);
	}

	void GameLevelOne::OnPlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
	{
		m_PlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
		if (!m_PlayerSpaceship.expired())
			m_PlayerSpaceship.lock()->OnActorDestroyed.Bind(GetWeakRef(), &GameLevelOne::OnPlayerSpaceshipDestroyed);
		else
			GameOver();
	}

	void GameLevelOne::GameOver()
	{
		m_GameplayHUD.lock()->GameFinished(false);
	}

	void GameLevelOne::Quit()
	{
		Application::Get().Quit();
	}

	void GameLevelOne::Restart()
	{
		PlayerManager::Get().Reset();
		Application::Get().LoadWorld<GameLevelOne>();
	}

	void GameLevelOne::SpawnCosmetics()
	{
		WeakRef<BackdropActor> backdropActor = SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");

		WeakRef<BackgroundLayer> planets = SpawnActor<BackgroundLayer>();
		planets.lock()->SetAssets(
			{
				"SpaceShooterRedux/PNG/Planets/Planet1.png",
				"SpaceShooterRedux/PNG/Planets/Planet2.png",
				"SpaceShooterRedux/PNG/Planets/Planet3.png",
				"SpaceShooterRedux/PNG/Planets/Planet4.png",
				"SpaceShooterRedux/PNG/Planets/Planet5.png",
				"SpaceShooterRedux/PNG/Planets/Planet6.png",
				"SpaceShooterRedux/PNG/Planets/Planet7.png"
			}
		);

		planets.lock()->SetSpriteCount(1);
		planets.lock()->SetSizes(1.f, 1.5f);
		planets.lock()->SetVelocities({0.f, 50.f}, {0.f, 80.f});
		
		WeakRef<BackgroundLayer> meteors = SpawnActor<BackgroundLayer>();
		meteors.lock()->SetAssets(
			{
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png"
			}
		);

		meteors.lock()->SetSpriteCount(20);
		meteors.lock()->SetSizes(.2f, .5f);
	}
}