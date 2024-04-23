#include "Widget/ValueGauge.h"
#include "Framework/AssetManager.h"

namespace ly
{
	ValueGauge::ValueGauge(const sf::Vector2f& size, float percent, const sf::Color& foregroundColor, const sf::Color& backgroundColor)
		: m_Font{AssetManager::Get().LoadFont()},
		m_HealthText{"", *m_Font},
		m_FrontBar{size},
		m_BackBar {size},
		m_Percent {percent},
		m_ForegroundColor{foregroundColor},
		m_BackgroundColor{backgroundColor}
	{
		m_FrontBar.setFillColor(m_ForegroundColor);
		m_BackBar.setFillColor(m_BackgroundColor);
	}

	void ValueGauge::UpdateValue(float value, float maxValue)
	{
		if (maxValue == 0)
			return;

		m_Percent = value / maxValue;
		const std::string str = std::to_string((int)value) + '/' + std::to_string((int)maxValue);
		m_HealthText.setString(str);

		const sf::Vector2f& barSize = m_BackBar.getSize();
		m_FrontBar.setSize({barSize.x * m_Percent, barSize.y});
	}

	void ValueGauge::Draw(sf::RenderWindow& window)
	{
		window.draw(m_BackBar);
		window.draw(m_FrontBar);
		window.draw(m_HealthText);
	}

	void ValueGauge::UpdatePosition(const sf::Vector2f& position)
	{
		m_HealthText.setPosition(position);
		m_FrontBar.setPosition(position);
		m_BackBar.setPosition(position);
	}

	void ValueGauge::UpdateRotation(float rotation)
	{
		m_HealthText.setRotation(rotation);
		m_FrontBar.setRotation(rotation);
		m_BackBar.setRotation(rotation);
	}
}