#pragma once

#include "Core/Core.h"
#include "Widget/Widget.h"

namespace ly
{
	class TextWidget : public Widget
	{
	public:
		TextWidget(const std::string& textStr, const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf", unsigned int characterSize = 10);

		inline void SetString(const std::string& str) { m_Text.setString(str); }
		inline void SetTextSize(unsigned int size) { m_Text.setCharacterSize(size); }
		inline void SetTextColor(const sf::Color& color) { m_Text.setColor(color); }

		inline sf::Text& GetText() { return m_Text; }
		inline Ref<sf::Font>& GetFont() { return m_Font; }

		virtual sf::FloatRect GetBounds() const override;

	private:
		virtual void Draw(sf::RenderWindow& window) override;
		virtual void UpdatePosition(const sf::Vector2f& position) override;
		virtual void UpdateRotation(float rotation) override;

	private:
		Ref<sf::Font> m_Font;
		sf::Text m_Text;
	};
}