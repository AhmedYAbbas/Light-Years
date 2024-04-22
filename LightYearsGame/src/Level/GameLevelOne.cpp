#include <Gameplay/WaitStage.h>

#include "Level/GameLevelOne.h"
#include "Player/PlayerSpaceship.h"
#include "Player/PlayerManager.h"
#include "Player/Player.h"

#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/HexagonStage.h"
#include "Enemy/UFOStage.h"

namespace ly
{
	GameLevelOne::GameLevelOne()
	{
	}

	void GameLevelOne::BeginPlay()
	{
		Player player = PlayerManager::Get().CreateNewPlayer();
		m_PlayerSpaceship = player.SpawnSpaceship(this);
		m_PlayerSpaceship.lock()->OnActorDestroyed.Bind(GetWeakRef(), &GameLevelOne::OnPlayerSpaceshipDestroyed);
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(Ref<UFOStage>{CreateRef<UFOStage>(this)});

		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 5.f)});
		AddStage(Ref<VanguardStage>{CreateRef<VanguardStage>(this)});

		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 15.f)});
		AddStage(Ref<TwinBladeStage>{CreateRef<TwinBladeStage>(this)});

		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 15.f)});
		AddStage(Ref<HexagonStage>{CreateRef<HexagonStage>(this)});
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
		LOG("==================GameOver==================");
	}
}