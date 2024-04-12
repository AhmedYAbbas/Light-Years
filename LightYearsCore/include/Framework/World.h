#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Core.h"

namespace ly
{
	class Actor;
	class Application;

	class World
	{
	public:
		World();
		virtual ~World() = default;

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		template<typename T>
		WeakRef<T> SpawnActor()
		{
			Ref<T> actor = CreateRef<T>(this);
			m_PendingActors.push_back(actor);
			return actor;
		}

		sf::Vector2u GetWindowSize() const;

	private:
		void BeginPlay();
		void Tick(float deltaTime);
		
	private:
		Vector<Ref<Actor>> m_Actors;
		Vector<Ref<Actor>> m_PendingActors;
		bool m_HasBegunPlay;
	};
}