#pragma once

#include <SFML/Graphics.hpp>

#include "Framework/Object.h"

namespace ly
{
	class HUD : public Object
	{
	public:
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual bool HandleEvent(const sf::Event& event);

		void NativeInit(const sf::RenderWindow& window);
		inline bool IsInit() const { return m_IsInit; }

	protected:
		HUD();

	private:
		virtual void Init(const sf::RenderWindow& window);

	private:
		bool m_IsInit;
	};
}