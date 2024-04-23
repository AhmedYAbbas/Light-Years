#include "Widget/TextWidget.h"
#include "Framework/AssetManager.h"

namespace ly
{
	TextWidget::TextWidget(const std::string& textStr, const std::string& fontPath, unsigned int characterSize)
		: m_Font{AssetManager::Get().LoadFont(fontPath)}, m_Text {textStr, *m_Font, characterSize}
	{
	}

	void TextWidget::Draw(sf::RenderWindow& window)
	{
		window.draw(m_Text);
	}

	void TextWidget::UpdatePosition(const sf::Vector2f position)
	{
		m_Text.setPosition(position);
	}

	void TextWidget::UpdateRotation(float rotation)
	{
		m_Text.setRotation(rotation);
	}
}