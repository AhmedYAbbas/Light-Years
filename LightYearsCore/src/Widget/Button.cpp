#include "Widget/Button.h"
#include "Framework/AssetManager.h"

namespace ly
{
	Button::Button(const std::string& textString, const std::string& texturePath)
		: m_Texture{AssetManager::Get().LoadTexture(texturePath)},
		m_Sprite{*m_Texture},
		m_TextWidget{textString},
		m_ButtonDefaultColor{128, 128, 128},
		m_ButtonDownColor{64, 64, 64},
		m_ButtonHoverColor{190, 190, 190},
		m_IsButtonDown{false}
	{
	}

	sf::FloatRect Button::GetBounds() const
	{
		return m_Sprite.getGlobalBounds();
	}

	void Button::Draw(sf::RenderWindow& window)
	{
		window.draw(m_Sprite);
		window.draw(m_TextWidget.GetText());
	}

	void Button::UpdatePosition(const sf::Vector2f& position)
	{
		m_Sprite.setPosition(position);
		m_TextWidget.GetText().setPosition(position);
	}

	void Button::UpdateRotation(float rotation)
	{
		m_Sprite.setRotation(rotation);
		m_TextWidget.GetText().setRotation(rotation);
	}
}