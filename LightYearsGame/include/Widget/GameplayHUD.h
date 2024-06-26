#pragma once

#include <Widget/HUD.h>
#include <Widget/TextWidget.h>
#include <Widget/ValueGauge.h>
#include <Widget/ImageWidget.h>
#include <Widget/Button.h>

namespace ly
{
	class Actor;

	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& window) override;
		virtual void Tick(float deltaTime) override;
		virtual bool HandleEvent(const sf::Event& event) override;

		void GameFinished(bool playerWon);

	private:
		virtual void Init(const sf::RenderWindow& window) override;
		void OnPlayerHealthUpdated(float amount, float currentHealth, float maxHealth);
		void OnPlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);
		void OnPlayerLifeCountUpdated(int count);
		void OnPlayerScoreChanged(int score);
		void RefreshHealthBar();
		void SetupPlayerStatus();

		void RestartButtonClicked();
		void QuitButtonClicked();

	public:
		Delegate<> OnRestartButtonClicked;
		Delegate<> OnQuitButtonClicked;

	private:
		TextWidget m_FrameRateText;
		ValueGauge m_PlayerHealthBar;
		ImageWidget m_PlayerLifeIcon;
		TextWidget m_PlayerLifeCountText;
		ImageWidget m_PlayerScoreIcon;
		TextWidget m_PlayerScoreText;

		sf::Color m_NormalHealthBarColor;
		sf::Color m_CriticalHealthBarColor;
		float m_CriticalThreshold;

		float m_WidgetSpacing;

		TextWidget m_WinLoseText;
		TextWidget m_FinalScoreText;
		Button m_RestartButton;
		Button m_QuitButton;
	};
}