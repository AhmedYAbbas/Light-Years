#include "Widget/ImageWidget.h"
#include "Framework/AssetManager.h"

namespace ly
{
	ImageWidget::ImageWidget(const std::string& imagePath)
		: m_Texture{AssetManager::Get().LoadTexture(imagePath)},
		m_Sprite{*m_Texture}
	{
	}

	void ImageWidget::SetImage(const Ref<sf::Texture> texture)
	{
		m_Texture = texture;
		m_Sprite.setTexture(*m_Texture);
	}

	sf::FloatRect ImageWidget::GetBounds() const
	{
		return m_Sprite.getGlobalBounds();
	}

	void ImageWidget::Draw(sf::RenderWindow& window)
	{
		window.draw(m_Sprite);
	}

	void ImageWidget::UpdatePosition(const sf::Vector2f& position)
	{
		m_Sprite.setPosition(position);
	}

	void ImageWidget::UpdateRotation(float rotation)
	{
		m_Sprite.setRotation(rotation);
	}
}