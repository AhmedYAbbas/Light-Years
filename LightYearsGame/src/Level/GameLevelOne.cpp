#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "Player/PlayerSpaceship.h"
#include "Enemy/VanguardStage.h"

namespace ly
{
	GameLevelOne::GameLevelOne()
	{
		m_PlayerSpaceship = SpawnActor<PlayerSpaceship>();
		m_PlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
	}

	void GameLevelOne::BeginPlay()
	{
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(Ref<VanguardStage>{CreateRef<VanguardStage>(this)});
	}
}