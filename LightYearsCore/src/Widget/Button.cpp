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
		m_Sprite.setColor(m_ButtonDefaultColor);
		CenterText();
	}

	sf::FloatRect Button::GetBounds() const
	{
		return m_Sprite.getGlobalBounds();
	}

	bool Button::HandleEvent(const sf::Event& event)
	{
		if (!IsVisible())
			return false;

		bool handled = Widget::HandleEvent(event);
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (m_Sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && m_IsButtonDown)
				{
					OnButtonClicked.Broadcast();
					handled = true;
				}
			}
			ButtonUp();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (m_Sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
			{
				ButtonDown();
				handled = true;
			}
		}
		else if (event.type == sf::Event::MouseMoved)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (m_Sprite.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				{
					ButtonHovered();
					handled = true;
				}
				else
					ButtonUp();

			}
		}

		return handled;
	}

	void Button::SetTextString(const std::string& str)
	{
		m_TextWidget.SetString(str);
		CenterText();
	}

	void Button::SetTextSize(unsigned int size)
	{
		m_TextWidget.SetTextSize(size);
		CenterText();
	}

	void Button::Draw(sf::RenderWindow& window)
	{
		window.draw(m_Sprite);
		window.draw(m_TextWidget.GetText());
	}

	void Button::UpdatePosition(const sf::Vector2f& position)
	{
		m_Sprite.setPosition(position);
		CenterText();
	}

	void Button::UpdateRotation(float rotation)
	{
		m_Sprite.setRotation(rotation);
		m_TextWidget.GetText().setRotation(rotation);
	}

	void Button::CenterText()
	{
		const sf::Vector2f widgetCenter = GetCenterPosition();
		sf::FloatRect textBounds = m_TextWidget.GetText().getGlobalBounds();
		m_TextWidget.GetText().setPosition(widgetCenter - sf::Vector2f {textBounds.width / 2.f, textBounds.height});
	}

	void Button::ButtonUp()
	{
		m_IsButtonDown = false;
		m_Sprite.setColor(m_ButtonDefaultColor);
	}

	void Button::ButtonDown()
	{
		m_IsButtonDown = true;
		m_Sprite.setColor(m_ButtonDownColor);
	}

	void Button::ButtonHovered()
	{
		m_Sprite.setColor(m_ButtonHoverColor);
	}
}