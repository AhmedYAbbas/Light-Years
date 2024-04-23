#include "Widget/GameplayHUD.h"

namespace ly
{
	GameplayHUD::GameplayHUD()
		: m_FrameRateText{"Frame Rate:"}
	{
		m_FrameRateText.SetTextSize(30);
	}

	void GameplayHUD::Draw(sf::RenderWindow& window)
	{
		m_FrameRateText.NativeDraw(window);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		HUD::Tick(deltaTime);
		int frameRate = (int)(1 / deltaTime);
		const std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		m_FrameRateText.SetString(frameRateStr);
	}
}