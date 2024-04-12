#include "Framework/Actor.h"
#include "Framework/AssetManager.h"

namespace ly
{
	Actor::Actor(World* world)
		: m_World{world}, m_HasBegunPlay{false}
	{
	}

	Actor::~Actor()
	{
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
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::SetTexture(const std::string& filepath)
	{
		AssetManager& assetManager = AssetManager::Get();
		m_Texture = assetManager.LoadTexture(filepath);
		if (m_Texture)
			m_Sprite.setTexture(*m_Texture, true);
	}
}