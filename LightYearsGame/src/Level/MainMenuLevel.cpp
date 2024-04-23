#include <Framework/Application.h>

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