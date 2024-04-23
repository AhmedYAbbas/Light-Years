#include <Widget/TextWidget.h>

#include "Widget/ValueGauge.h"
#include "Framework/AssetManager.h"

namespace ly
{
	ValueGauge::ValueGauge(const sf::Vector2f& size, float percent, const sf::Color& foregroundColor, const sf::Color& backgroundColor)
		: m_HealthTextWidget {""}, 
		m_FrontBar{size},
		m_BackBar {size},
		m_Percent {percent},
		m_ForegroundColor{foregroundColor},
		m_BackgroundColor{backgroundColor}
	{
		m_FrontBar.setFillColor(m_ForegroundColor);
		m_BackBar.setFillColor(m_BackgroundColor);
		m_HealthTextWidget.SetTextSize(20);
	}

	void ValueGauge::UpdateValue(float value, float maxValue)
	{
		if (maxValue == 0)
			return;

		m_Percent = value / maxValue;
		const std::string str = std::to_string((int)value) + '/' + std::to_string((int)maxValue);
		m_HealthTextWidget.GetText().setString(str);
		CenterText();

		const sf::Vector2f& barSize = m_BackBar.getSize();
		m_FrontBar.setSize({barSize.x * m_Percent, barSize.y});
	}

	sf::FloatRect ValueGauge::GetBounds() const
	{
		return m_BackBar.getGlobalBounds();
	}

	void ValueGauge::SetForegroundColor(const sf::Color& color)
	{
		m_ForegroundColor = color;
		m_FrontBar.setFillColor(m_ForegroundColor);
	}

	void ValueGauge::SetBackgroundColor(const sf::Color& color)
	{
		m_BackgroundColor = color;
		m_BackBar.setFillColor(m_BackgroundColor);
	}

	void ValueGauge::Draw(sf::RenderWindow& window)
	{
		window.draw(m_BackBar);
		window.draw(m_FrontBar);
		window.draw(m_HealthTextWidget.GetText());
	}

	void ValueGauge::UpdatePosition(const sf::Vector2f& position)
	{
		m_FrontBar.setPosition(position);
		m_BackBar.setPosition(position);
		CenterText();
	}

	void ValueGauge::UpdateRotation(float rotation)
	{
		m_FrontBar.setRotation(rotation);
		m_BackBar.setRotation(rotation);
	}

	void ValueGauge::CenterText()
	{
		const sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBounds = m_HealthTextWidget.GetText().getGlobalBounds();
		m_HealthTextWidget.GetText().setPosition(widgetCenter - sf::Vector2f{textBounds.width / 2.f, textBounds.height});
	}
}