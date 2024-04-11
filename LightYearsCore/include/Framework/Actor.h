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

		inline World* GetWorld() const { return m_World; }

	protected:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);

	private:
		World* m_World;
		bool m_HasBegunPlay;

		sf::Sprite m_Sprite;
		sf::Texture m_Texture;
	};
}