#pragma once

#include "Widget/Widget.h"
#include "Widget/TextWidget.h"
#include "Framework/Delegate.h"

namespace ly
{
	class Button : public Widget
	{
	public:
		Button(const std::string& textString = "Button", const std::string& texturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");

		virtual sf::FloatRect GetBounds() const override;
		inline TextWidget& GetTextWidget() { return m_TextWidget; }

	private:
		virtual void Draw(sf::RenderWindow& window) override;
		virtual void UpdatePosition(const sf::Vector2f& position) override;
		virtual void UpdateRotation(float rotation) override;

	private:
		Ref<sf::Texture> m_Texture;
		sf::Sprite m_Sprite;
		TextWidget m_TextWidget;

		sf::Color m_ButtonDefaultColor;
		sf::Color m_ButtonDownColor;
		sf::Color m_ButtonHoverColor;

		bool m_IsButtonDown;
	};
}