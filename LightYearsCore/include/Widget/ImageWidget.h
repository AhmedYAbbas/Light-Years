#pragma once

#include <SFML/Graphics.hpp>

#include "Widget/Widget.h"

namespace ly
{
	class ImageWidget : public Widget
	{
	public:
		ImageWidget(const std::string& imagePath);

		void SetImage(const Ref<sf::Texture> texture);
		virtual sf::FloatRect GetBounds() const override;

	private:
		virtual void Draw(sf::RenderWindow& window) override;
		virtual void UpdatePosition(const sf::Vector2f& position) override;
		virtual void UpdateRotation(float rotation) override;

	private:
		Ref<sf::Texture> m_Texture;
		sf::Sprite m_Sprite;
	};
}