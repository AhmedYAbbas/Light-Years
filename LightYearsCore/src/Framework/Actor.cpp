#include <box2d/b2_body.h>

#include "Framework/Actor.h"
#include "Framework/AssetManager.h"
#include "Framework/PhysicsSystem.h"

namespace ly
{
	Actor::Actor(World* world, const std::string& filepath)
		: m_World{world}, m_HasBegunPlay{false}, m_PhysicsBody{nullptr}, m_PhysicsEnabled{false}
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

	bool Actor::IsActorOutOfWindowBounds() const
	{
		const float windowWidth = GetWindowSize().x;
		const float windowHeight = GetWindowSize().y;

		const float width = GetActorGlobalBounds().width;
		const float height = GetActorGlobalBounds().height;

		const sf::Vector2f& pos = GetActorLocation();

		if (pos.x < -width)					return true;
		if (pos.x > windowWidth + width)	return true;
		if (pos.y < -height)				return true;
		if (pos.y > windowHeight + height)	return true;

		return false;
	}

	void Actor::SetEnablePhysics(bool enable)
	{
		m_PhysicsEnabled = enable;
		if (m_PhysicsEnabled)
			InitializePhysics();
		else
			UninitializePhysics();
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

	void Actor::InitializePhysics()
	{
		if (!m_PhysicsBody)
			m_PhysicsBody = PhysicsSystem::Get().AddListener(this);
	}

	void Actor::UninitializePhysics()
	{
		if (m_PhysicsBody)
			PhysicsSystem::Get().RemoveListener(m_PhysicsBody);
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (m_PhysicsBody)
		{
			const float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			const b2Vec2 pos {GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale};
			const float rotation = Math::DegToRad(GetActorRotation());

			m_PhysicsBody->SetTransform(pos, rotation);
		}
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