#include "Framework/BackgroundLayer.h"
#include "Framework/AssetManager.h"
#include "Utility/Math.h"

namespace ly
{
	BackgroundLayer::BackgroundLayer(World* world, const Vector<std::string>& assetsPath, const sf::Vector2f& minVelocity, const sf::Vector2f& maxVelocity, float minSize, float maxSize, int spriteCount, const sf::Color tint)
		: Actor{world},
		m_MinVelocity{minVelocity},
		m_MaxVelocity{maxVelocity},
		m_MinSize{minSize},
		m_MaxSize{maxSize},
		m_SpriteCount{spriteCount},
		m_TintColor{tint}
	{
		SetEnablePhysics(false);
		SetAssets(assetsPath);
	}

	void BackgroundLayer::Render(sf::RenderWindow& window)
	{
		Actor::Render(window);

		for (sf::Sprite& sprite : m_Sprites)
			window.draw(sprite);
	}

	void BackgroundLayer::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		for (int i = 0; i < m_Sprites.size(); ++i)
		{
			sf::Sprite& sprite = m_Sprites[i];
			const sf::Vector2f& velocity = m_Velocities[i];

			sprite.setPosition(sprite.getPosition() + velocity * deltaTime);
			if (IsSpriteOffScreen(sprite))
			{
				RandomSpriteTexture(sprite);
				RandomSpriteTransform(sprite);
				float xVelocity = Math::RandomRange(m_MinVelocity.x, m_MaxVelocity.x);
				float yVelocity = Math::RandomRange(m_MinVelocity.y, m_MaxVelocity.y);
				m_Velocities[i] = {xVelocity, yVelocity};
			}
		}
	}

	void BackgroundLayer::SetAssets(const Vector<std::string>& assetsPath)
	{
		for (const std::string& texturePath : assetsPath)
		{
			Ref<sf::Texture> texture = AssetManager::Get().LoadTexture(texturePath);
			m_Textures.push_back(texture);
		}
		RefreshSprites();
	}

	void BackgroundLayer::RefreshSprites()
	{
		m_Sprites.clear();
		m_Velocities.clear();

		for (int i = 0; i < m_SpriteCount; ++i)
		{
			sf::Sprite sprite;
			RandomSpriteTexture(sprite);
			RandomSpriteTransform(sprite, true);
			m_Sprites.push_back(sprite);

			float xVelocity = Math::RandomRange(m_MinVelocity.x, m_MaxVelocity.x);
			float yVelocity = Math::RandomRange(m_MinVelocity.y, m_MaxVelocity.y);
			m_Velocities.push_back(sf::Vector2f {xVelocity, yVelocity});
		}
		SetColorTint(m_TintColor);
	}

	void BackgroundLayer::RandomSpriteTexture(sf::Sprite& sprite)
	{
		if (!m_Textures.empty())
		{
			Ref<sf::Texture> texture = GetRandomTexture();
			sprite.setTexture(*texture, true);
			sf::FloatRect bounds = sprite.getGlobalBounds();
			sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		}
	}

	Ref<sf::Texture> BackgroundLayer::GetRandomTexture() const
	{
		int index = Math::RandomRange(0, m_Textures.size() - 1);
		return m_Textures[index];
	}

	void BackgroundLayer::RandomSpriteTransform(sf::Sprite& sprite, bool randomY)
	{
		RandomSpritePosition(sprite, randomY);
		RandomSpriteRotation(sprite);
		RandomSpriteSize(sprite);
	}

	void BackgroundLayer::RandomSpritePosition(sf::Sprite& sprite, bool randomY)
	{
		const auto windowSize = GetWindowSize();
		const auto bounds = sprite.getGlobalBounds();

		float xPos = Math::RandomRange(0.f, windowSize.x);
		float yPos = randomY ? Math::RandomRange(0.f, windowSize.y) : -bounds.height;
		sprite.setPosition(xPos, yPos);
	}

	void BackgroundLayer::RandomSpriteRotation(sf::Sprite& sprite)
	{
		sprite.setRotation(Math::RandomRange(0.f, 360.f));
	}

	void BackgroundLayer::RandomSpriteSize(sf::Sprite& sprite)
	{
		float size = Math::RandomRange(m_MinSize, m_MaxSize);
		sprite.setScale(size, size);
	}

	void BackgroundLayer::SetColorTint(const sf::Color& color)
	{
		m_TintColor = color;
		for (sf::Sprite& sprite : m_Sprites)
			sprite.setColor(color);
	}

	void BackgroundLayer::SetSpriteCount(int count)
	{
		m_SpriteCount = count;
		RefreshSprites();
	}

	void BackgroundLayer::SetVelocities(const sf::Vector2f& min, const sf::Vector2f& max)
	{
		m_MinVelocity = min;
		m_MaxVelocity = max;
		for (auto& velocity : m_Velocities)
		{
			float xVelocity = Math::RandomRange(m_MinVelocity.x, m_MaxVelocity.x);
			float yVelocity = Math::RandomRange(m_MinVelocity.y, m_MaxVelocity.y);
			velocity = {xVelocity, yVelocity};
		}
	}

	void BackgroundLayer::SetSizes(float min, float max)
	{
		m_MinSize = min;
		m_MaxSize = max;
		for (auto& sprite : m_Sprites)
			RandomSpriteSize(sprite);
	}

	bool BackgroundLayer::IsSpriteOffScreen(const sf::Sprite& sprite) const
	{
		const auto bounds = sprite.getGlobalBounds();
		const auto windowSize = GetWindowSize();
		const auto spritePosition = sprite.getPosition();

		if (spritePosition.x < -bounds.width || spritePosition.x > windowSize.x + bounds.width)
			return true;
		if (spritePosition.y < -bounds.height|| spritePosition.y > windowSize.y + bounds.height)
			return true;

		return false;
	}
}