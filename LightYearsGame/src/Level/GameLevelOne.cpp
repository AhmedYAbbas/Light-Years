#include <Gameplay/WaitStage.h>

#include "Level/GameLevelOne.h"
#include "Player/PlayerSpaceship.h"

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
}