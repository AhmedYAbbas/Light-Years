#include <Framework/Application.h>
#include <Framework/BackdropActor.h>

#include "Level/MainMenuLevel.h"
#include "Level/GameLevelOne.h"
#include "Widget/MainMenuHUD.h"

namespace ly
{
	MainMenuLevel::MainMenuLevel()
		: m_MainMenuHUD{SpawnHUD<MainMenuHUD>()}
	{
	}

	void MainMenuLevel::BeginPlay()
	{
		m_MainMenuHUD.lock()->OnStartButtonClicked.Bind(GetWeakRef(), &MainMenuLevel::StartGame);
		m_MainMenuHUD.lock()->OnQuitButtonClicked.Bind(GetWeakRef(), &MainMenuLevel::QuitGame);
		SpawnActor<BackdropActor>("SpaceShooterRedux/mainMenuBg.png", sf::Vector2f{0.f, 0.f});
	}

	void MainMenuLevel::StartGame()
	{
		Application::Get().LoadWorld<GameLevelOne>();
	}

	void MainMenuLevel::QuitGame()
	{
		Application::Get().Quit();
	}
}