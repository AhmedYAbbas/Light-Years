#include <Core/EntryPoint.h>

#include "GameFramework/Game.h"

ly::Application* ly::CreateApplication()
{
	return new Game();
}

Game::Game()
{
	WeakRef<ly::World> world = LoadWorld<ly::World>();
	world.lock()->SpawnActor<ly::Actor>();
	actorToDestroy = world.lock()->SpawnActor<ly::Actor>();
}

void Game::Render()
{
	Application::Render();
}

void Game::Tick(float deltaTime)
{
	Application::Tick(deltaTime);

	counter += deltaTime;
	if (counter >= 2.f)
	{
		if (!actorToDestroy.expired())
			actorToDestroy.lock()->Destroy();
	}
}
