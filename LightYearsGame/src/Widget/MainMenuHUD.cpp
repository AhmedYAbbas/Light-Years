#include "Widget/MainMenuHUD.h"

namespace ly
{
	MainMenuHUD::MainMenuHUD()
		: m_TitleText{"Light Years"},
		m_StartButton{"Start"},
		m_QuitButton{"Quit"}
	{
		m_TitleText.SetTextSize(40);
		m_StartButton.SetTextSize(20);
		m_QuitButton.SetTextSize(20);
	}

	void MainMenuHUD::Draw(sf::RenderWindow& window)
	{
		m_TitleText.NativeDraw(window);
		m_StartButton.NativeDraw(window);
		m_QuitButton.NativeDraw(window);
	}

	bool MainMenuHUD::HandleEvent(const sf::Event& event)
	{
		return m_StartButton.HandleEvent(event) || m_QuitButton.HandleEvent(event) || HUD::HandleEvent(event);
	}

	void MainMenuHUD::Init(const sf::RenderWindow& window)
	{
		const auto windowSize = window.getSize();
		m_TitleText.SetWidgetPosition({windowSize.x / 2.f - m_TitleText.GetBounds().width / 2.f, 100.f});

		m_StartButton.SetWidgetPosition({windowSize.x / 2.f - m_StartButton.GetBounds().width / 2.f, windowSize.y / 2.f});
		m_QuitButton.SetWidgetPosition(m_StartButton.GetWidgetPosition() + sf::Vector2f{0.f, 50.f});

		m_StartButton.OnButtonClicked.Bind(GetWeakRef(), &MainMenuHUD::StartButtonClicked);
		m_QuitButton.OnButtonClicked.Bind(GetWeakRef(), &MainMenuHUD::QuitButtonClicked);
	}

	void MainMenuHUD::StartButtonClicked()
	{
		OnStartButtonClicked.Broadcast();
	}

	void MainMenuHUD::QuitButtonClicked()
	{
		OnQuitButtonClicked.Broadcast();
	}
}