#include "Framework/Actor.h"

namespace ly
{
	Actor::Actor(World* world)
		: m_World{world}, m_HasBegunPlay{false}
	{
	}

	Actor::~Actor()
	{
		LOG("Actor Destroyed!");
	}

	void Actor::BeginPlayInternal()
	{
		if (!m_HasBegunPlay)
		{
			m_HasBegunPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
			Tick(deltaTime);
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(m_Sprite);
	}

	void Actor::BeginPlay()
	{
		LOG("Actor Began Play!");
	}

	void Actor::Tick(float deltaTime)
	{
		LOG("Actor is ticking.");
	}

	void Actor::SetTexture(const std::string& filepath)
	{
		if (m_Texture.loadFromFile(filepath))
		{
			m_Sprite.setTexture(m_Texture, true);
		}
	}
}