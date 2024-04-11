#include <Core/EntryPoint.h>

#include "GameFramework/Game.h"

ly::Application* ly::CreateApplication()
{
	return new Game();
}

Game::Game()
	: Application{600, 980, "Light Years", sf::Style::Close | sf::Style::Titlebar}
{
	WeakRef<ly::World> world = LoadWorld<ly::World>();
	world.lock()->SpawnActor<ly::Actor>();
	actorToDestroy = world.lock()->SpawnActor<ly::Actor>();
	actorToDestroy.lock()->SetTexture("assets/SpaceShooterRedux/PNG/playerShip1_blue.png");
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
