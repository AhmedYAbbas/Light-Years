#pragma once

#include "Framework/Actor.h"

namespace ly
{
	class BackgroundLayer : public Actor
	{
	public:
		BackgroundLayer(World* world,
			const Vector<std::string>& assetsPath = {},
			const sf::Vector2f& minVelocity = {0.f, 50.f},
			const sf::Vector2f& maxVelocity = {0.f, 200.f},
			float minSize = 1.f,
			float maxSize = 2.f,
			int spriteCount = 20,
			const sf::Color tint = {180, 180, 200, 225}
		);

		void SetAssets(const Vector<std::string>& assetsPath);
		void SetColorTint(const sf::Color& color);
		void SetSpriteCount(int count);
		void SetVelocities(const sf::Vector2f& min, const sf::Vector2f& max);
		void SetSizes(float min, float max);

		virtual void Render(sf::RenderWindow& window) override;

	protected:
		virtual void Tick(float deltaTime) override;

	private:
		void RefreshSprites();
		void RandomSpriteTexture(sf::Sprite& sprite);
		Ref<sf::Texture> GetRandomTexture() const;
		void RandomSpriteTransform(sf::Sprite& sprite, bool randomY = false);
		void RandomSpritePosition(sf::Sprite& sprite, bool randomY = false);
		void RandomSpriteRotation(sf::Sprite& sprite);
		void RandomSpriteSize(sf::Sprite& sprite);
		bool IsSpriteOffScreen(const sf::Sprite& sprite) const;

	private:
		sf::Vector2f m_MinVelocity;
		sf::Vector2f m_MaxVelocity;
		float m_MinSize;
		float m_MaxSize;
		int m_SpriteCount;
		sf::Color m_TintColor;

		Vector<Ref<sf::Texture>> m_Textures;
		Vector<sf::Sprite> m_Sprites;
		Vector<sf::Vector2f> m_Velocities;
	};
}