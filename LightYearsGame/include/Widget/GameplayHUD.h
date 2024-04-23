#pragma once

#include <Widget/HUD.h>
#include <Widget/TextWidget.h>
#include <Widget/ValueGauge.h>
#include <Widget/ImageWidget.h>

namespace ly
{
	class Actor;

	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& window) override;
		virtual void Tick(float deltaTime) override;

	private:
		virtual void Init(const sf::RenderWindow& window) override;
		void OnPlayerHealthUpdated(float amount, float currentHealth, float maxHealth);
		void OnPlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);
		void OnPlayerLifeCountUpdated(int count);
		void OnPlayerScoreChanged(int score);

		void RefreshHealthBar();
		void SetupPlayerStatus();

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
	};
}