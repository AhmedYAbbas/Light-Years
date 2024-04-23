#pragma once

#include <Widget/HUD.h>
#include <Widget/TextWidget.h>

namespace ly
{
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& window) override;
		virtual void Tick(float deltaTime) override;

	private:
		TextWidget m_FrameRateText;
	};
}