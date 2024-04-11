#include <Core/EntryPoint.h>

#include "GameFramework/Game.h"

ly::Application* ly::CreateApplication()
{
	return new Game();
}

Game::Game()
{
	LoadWorld<ly::World>();
}

void Game::Render()
{
	Application::Render();
}

void Game::Tick(float deltaTime)
{
	Application::Tick(deltaTime);
}
