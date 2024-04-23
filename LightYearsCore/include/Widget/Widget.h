#pragma once

#include <SFML/Graphics.hpp>

#include "Framework/Object.h"

namespace ly
{
	class Widget : public Object
	{
	public:
		void NativeDraw(sf::RenderWindow& window);
		virtual bool HandleEvent(const sf::Event& event);

		void SetWidgetPosition(const sf::Vector2f& position);
		void SetWidgetRotation(float rotation);

		inline const sf::Vector2f& GetWidgetPosition() const { return m_Transform.getPosition(); }
		inline float GetWidgetRotation() const { return m_Transform.getRotation(); }

		inline void SetVisibility(bool visibility) { m_IsVisible = visibility; }
		inline bool IsVisible() const { return m_IsVisible; }

		virtual sf::FloatRect GetBounds() const = 0;
		sf::Vector2f GetCenterPosition() const;

	protected:
		Widget();

	private:
		virtual void Draw(sf::RenderWindow& window);
		virtual void UpdatePosition(const sf::Vector2f& position);
		virtual void UpdateRotation(float rotation);

	private:
		sf::Transformable m_Transform;
		bool m_IsVisible;
	};
}