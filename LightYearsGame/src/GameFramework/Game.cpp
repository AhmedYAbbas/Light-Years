#include <Core/EntryPoint.h>

#include "config.h"
#include "GameFramework/Game.h"
#include "Player/PlayerSpaceship.h"
#include "Framework/AssetManager.h"

namespace ly
{
	Application* CreateApplication()
	{
		return new Game();
	}

	Game::Game()
		: Application {600, 980, "Light Years", sf::Style::Close | sf::Style::Titlebar}
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		WeakRef<World> world = LoadWorld<World>();
		playerSpaceship = world.lock()->SpawnActor<PlayerSpaceship>();
		playerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 490.f));
	}

	void Game::Render()
	{
		Application::Render();
	}

	void Game::Tick(float deltaTime)
	{
		Application::Tick(deltaTime);
	}
}
