#include <Gameplay/WaitStage.h>

#include "Level/GameLevelOne.h"
#include "Player/PlayerSpaceship.h"

#include "Enemy/VanguardStage.h"
#include "Enemy/TwinBladeStage.h"
#include "Enemy/HexagonStage.h"

#include "Enemy/UFO.h"

namespace ly
{
	GameLevelOne::GameLevelOne()
	{
		m_PlayerSpaceship = SpawnActor<PlayerSpaceship>();
		m_PlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
	}

	void GameLevelOne::BeginPlay()
	{
		WeakRef<UFO> ufo = SpawnActor<UFO>();
		ufo.lock()->SetActorLocation({GetWindowSize().x / 2.f, GetWindowSize().y / 2.f});
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 5.f)});
		AddStage(Ref<VanguardStage>{CreateRef<VanguardStage>(this)});

		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 15.f)});
		AddStage(Ref<TwinBladeStage>{CreateRef<TwinBladeStage>(this)});

		AddStage(Ref<WaitStage>{CreateRef<WaitStage>(this, 15.f)});
		AddStage(Ref<HexagonStage>{CreateRef<HexagonStage>(this)});
	}
}