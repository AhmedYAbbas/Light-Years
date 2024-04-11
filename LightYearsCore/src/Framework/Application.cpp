#include <iostream>

#include "framework/Application.h"

namespace ly
{
	Application::Application()
		: m_Window{sf::VideoMode(600, 800), "LightYears"}, m_TargetFrameRate{60.f}, m_TargetDeltaTime{1.f / m_TargetFrameRate}, m_TickClock {}
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

	void Application::Tick(float deltaTime)
	{
		std::cout << "Framerate: " << 1.f / deltaTime << "\n";
	}

	void Application::Render()
	{
		sf::RectangleShape rect {sf::Vector2f{100.f, 100.f}};
		rect.setOrigin(50.f, 50.f);
		rect.setFillColor(sf::Color::Cyan);
		rect.setPosition(m_Window.getSize().x / 2.f, m_Window.getSize().y / 2.f);

		m_Window.draw(rect);
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	void Application::RenderInternal()
	{
		m_Window.clear();
		Render();
		m_Window.display();
	}
}