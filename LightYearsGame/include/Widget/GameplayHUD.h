#pragma once

#include <Widget/HUD.h>
#include <Widget/TextWidget.h>
#include <Widget/ValueGauge.h>

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
		void RefreshHealthBar();

	private:
		TextWidget m_FrameRateText;
		ValueGauge m_PlayerHealthBar;
		sf::Color m_NormalHealthBarColor;
		sf::Color m_CriticalHealthBarColor;
		float m_CriticalThreshold;
	};
}