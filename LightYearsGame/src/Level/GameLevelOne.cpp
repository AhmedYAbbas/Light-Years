#include <Gameplay/WaitStage.h>
#include <Framework/Application.h>

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
}