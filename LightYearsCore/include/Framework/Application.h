#pragma once

#include <SFML/Graphics.hpp>

namespace ly
{
	class Application
	{
	public:
		Application();
		void Run();

	private:
		virtual void Tick(float deltaTime);
		virtual void Render();

		void TickInternal(float deltaTime);
		void RenderInternal();

	private:
		sf::RenderWindow m_Window;
		sf::Clock m_TickClock;
		float m_TargetFrameRate;
		float m_TargetDeltaTime;
	};

	Application* CreateApplication();
}