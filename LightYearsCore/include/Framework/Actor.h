#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Core.h"
#include "Framework/Object.h"

namespace ly
{
	class World;

	class Actor : public Object
	{
	public:
		Actor(World* world);
		virtual ~Actor();

		void BeginPlayInternal();
		void TickInternal(float deltaTime);

		void SetTexture(const std::string& filepath);
		void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& pos);
		void SetActorRotation(float angle);
		void AddActorLocationOffset(const sf::Vector2f& offset);
		void AddActorRotationOffset(float offset);

		inline const sf::Vector2f& GetActorLocation() const { return m_Sprite.getPosition(); }
		inline float GetActorRotation() const { return m_Sprite.getRotation(); }
		inline sf::Vector2f GetForwardDirection();
		inline sf::Vector2f GetRightDirection();

		inline World* GetWorld() const { return m_World; }

	protected:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

	private:
		void CenterPivot();

	private:
		World* m_World;
		bool m_HasBegunPlay;

		sf::Sprite m_Sprite;
		Ref<sf::Texture> m_Texture;
	};
}