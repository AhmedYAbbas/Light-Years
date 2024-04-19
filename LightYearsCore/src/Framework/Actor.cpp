#include "Framework/Actor.h"
#include "Framework/AssetManager.h"

namespace ly
{
	Actor::Actor(World* world, const std::string& filepath)
		: m_World{world}, m_HasBegunPlay{false}
	{
		SetTexture(filepath);
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

	void Actor::SetActorLocation(const sf::Vector2f& pos)
	{
		m_Sprite.setPosition(pos);
	}

	void Actor::SetActorRotation(float angle)
	{
		m_Sprite.setRotation(angle);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f& offset)
	{
		SetActorLocation(GetActorLocation() + offset);
	}

	void Actor::AddActorRotationOffset(float offset)
	{
		SetActorRotation(GetActorRotation() + offset);
	}

	void Actor::BeginPlay()
	{
	}

	void Actor::Tick(float deltaTime)
	{
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bounds = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	}

	void Actor::SetTexture(const std::string& filepath)
	{
		AssetManager& assetManager = AssetManager::Get();
		m_Texture = assetManager.LoadTexture(filepath);
		if (m_Texture)
		{
			m_Sprite.setTexture(*m_Texture, true);
			CenterPivot();
		}
	}
}