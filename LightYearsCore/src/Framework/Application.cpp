#include "Core/Core.h"
#include "Framework/Application.h"
#include "Framework/World.h"

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, uint32_t style)
		: m_Window{sf::VideoMode(windowWidth, windowHeight), title, style}, m_TickClock {}, m_TargetFrameRate{60.f}, m_TargetDeltaTime{1.f / m_TargetFrameRate}, m_CurrentWorld{nullptr}
	{
	}

	void Application::Run()
	{
		m_TickClock.restart();
		float elapsedTime = 0.f;
		while (m_Window.isOpen())
		{
			sf::Event event;
			while (m_Window.pollEvent(event))
			{
				if (event.type == sf::Event::EventType::Closed)
				{
					m_Window.close();
				}
			}

			float frameDeltaTime = m_TickClock.restart().asSeconds();
			elapsedTime += frameDeltaTime;
			while (elapsedTime > m_TargetDeltaTime)
			{
				elapsedTime -= m_TargetDeltaTime;
				TickInternal(m_TargetDeltaTime);
				RenderInternal();
			}
		}
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
		if (m_CurrentWorld)
		{
			m_CurrentWorld->TickInternal(deltaTime);
		}
	}

	void Application::RenderInternal()
	{
		m_Window.clear();
		Render();
		m_Window.display();
	}

	void Application::Render()
	{
		if (m_CurrentWorld)
			m_CurrentWorld->Render(m_Window);
	}

	void Application::Tick(float deltaTime)
	{
	}
}