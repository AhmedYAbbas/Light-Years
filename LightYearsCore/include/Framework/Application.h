#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Core.h"
#include "Framework/World.h"

namespace ly
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;
		
		void Run();

		template<typename T>
		inline WeakRef<T> LoadWorld()
		{
			Ref<T> newWorld = CreateRef<T>();
			m_CurrentWorld = newWorld;
			m_CurrentWorld->BeginPlay();
			return newWorld;
		}

	protected:
		virtual void Tick(float deltaTime);
		virtual void Render();

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();

	private:
		sf::RenderWindow m_Window;
		sf::Clock m_TickClock;
		float m_TargetFrameRate;
		float m_TargetDeltaTime;
		
		Ref<World> m_CurrentWorld;
	};

	Application* CreateApplication();
}