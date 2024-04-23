#include "Widget/HUD.h"

namespace ly
{
	bool HUD::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	void HUD::Tick(float deltaTime)
	{
	}

	void HUD::NativeInit(const sf::RenderWindow& window)
	{
		if (!m_IsInit)
		{
			m_IsInit = true;
			Init(window);
		}
	}

	HUD::HUD()
		: m_IsInit{false}
	{
	}

	void HUD::Init(const sf::RenderWindow& window)
	{
	}
}