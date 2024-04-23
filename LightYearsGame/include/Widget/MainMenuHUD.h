#pragma once

#include <Widget/HUD.h>
#include <Widget/Button.h>
#include <Widget/TextWidget.h>

namespace ly
{
	class MainMenuHUD : public HUD
	{
	public:
		MainMenuHUD();

		virtual void Draw(sf::RenderWindow& window) override;
		virtual bool HandleEvent(const sf::Event& event) override;

	private:
		virtual void Init(const sf::RenderWindow& window) override;

		void StartButtonClicked();
		void QuitButtonClicked();

	public:
		Delegate<> OnStartButtonClicked;
		Delegate<> OnQuitButtonClicked;

	private:
		TextWidget m_TitleText;
		Button m_StartButton;
		Button m_QuitButton;
	};
}