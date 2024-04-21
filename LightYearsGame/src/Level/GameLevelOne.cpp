#include <Framework/TimerManager.h>

#include "Level/GameLevelOne.h"
#include "Enemy/Vanguard.h"
#include "Player/PlayerSpaceship.h"

namespace ly
{
	GameLevelOne::GameLevelOne()
	{
		playerSpaceship = SpawnActor<PlayerSpaceship>();
		playerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));

		WeakRef<Vanguard> vanguard = SpawnActor<Vanguard>();
		vanguard.lock()->SetActorLocation(sf::Vector2f(100.f, 50.f));
	}

	void GameLevelOne::BeginPlay()
	{
		TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback, 2.f, true);
	}

	void GameLevelOne::TimerCallback()
	{
		LOG("Timer Callback!");
	}
}