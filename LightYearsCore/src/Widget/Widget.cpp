#include "Widget/Widget.h"

namespace ly
{
	void Widget::NativeDraw(sf::RenderWindow& window)
	{
		if (m_IsVisible)
			Draw(window);
	}

	bool Widget::HandleEvent(const sf::Event& event)
	{
		return false;
	}

	void Widget::SetWidgetPosition(const sf::Vector2f& position)
	{
		m_Transform.setPosition(position);
		UpdatePosition(position);
	}

	void Widget::SetWidgetRotation(float rotation)
	{
		m_Transform.setRotation(rotation);
		UpdateRotation(rotation);
	}

	Widget::Widget()
		: m_Transform{}, m_IsVisible{true}
	{
	}

	void Widget::Draw(sf::RenderWindow& window)
	{
	}

	void Widget::UpdatePosition(const sf::Vector2f& location)
	{
	}

	void Widget::UpdateRotation(float rotation)
	{
	}
}