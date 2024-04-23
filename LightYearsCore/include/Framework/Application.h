#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Core.h"
#include "Framework/World.h"

namespace ly
{
	class Application
	{
	public:
		virtual ~Application() = default;
		
		static Application& Get() { return *s_Instance; }
		void Run();

		template<typename T>
		inline WeakRef<T> LoadWorld()
		{
			Ref<T> newWorld = CreateRef<T>();
			m_CurrentWorld = newWorld;
			m_CurrentWorld->BeginPlayInternal();
			return newWorld;
		}

		sf::RenderWindow& GetWindow() { return m_Window; }
		const sf::RenderWindow& GetWindow() const { return m_Window; }
		sf::Vector2u GetWindowSize() const { return m_Window.getSize(); }

	protected:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, uint32_t style);

		virtual void Tick(float deltaTime);
		virtual void Render();

	private:
		void TickInternal(float deltaTime);
		void RenderInternal();
		bool DispatchEvent(const sf::Event& event);

	private:
		sf::RenderWindow m_Window;
		sf::Clock m_TickClock;
		float m_TargetFrameRate;
		float m_TargetDeltaTime;
		
		Ref<World> m_CurrentWorld;
		sf::Clock m_CleanCycleClock;
		float m_CleanCycleInterval;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}