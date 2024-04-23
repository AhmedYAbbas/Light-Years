#pragma once

#include "Widget/Widget.h"

namespace ly
{
	class TextWidget;

	class ValueGauge : public Widget
	{
	public:
		ValueGauge(const sf::Vector2f& size = {200.f, 30.f}, float percent = 0.75f, const sf::Color& foregroundColor = {128, 255, 128}, const sf::Color& backgroundColor = {128, 128, 128});

		void UpdateValue(float value, float maxValue);
		virtual sf::FloatRect GetBounds() const override;

		void SetForegroundColor(const sf::Color& color);
		void SetBackgroundColor(const sf::Color& color);

	private:
		virtual void Draw(sf::RenderWindow& window) override;
		virtual void UpdatePosition(const sf::Vector2f& position) override;
		virtual void UpdateRotation(float rotation) override;

		void CenterText();

	private:
		TextWidget m_HealthTextWidget;

		sf::RectangleShape m_FrontBar;
		sf::RectangleShape m_BackBar;

		sf::Color m_ForegroundColor;
		sf::Color m_BackgroundColor;

		float m_Percent;
	};
}