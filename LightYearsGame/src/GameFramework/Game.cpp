#include <Core/EntryPoint.h>

#include "config.h"
#include "GameFramework/Game.h"
#include "Framework/AssetManager.h"
#include "Level/GameLevelOne.h"

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
		WeakRef<GameLevelOne> world = LoadWorld<GameLevelOne>();
	}
}
