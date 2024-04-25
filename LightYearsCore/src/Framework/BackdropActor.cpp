#include "Framework/BackdropActor.h"

namespace ly
{
	BackdropActor::BackdropActor(World* world, const std::string& texturePath, const sf::Vector2f velocity)
		: Actor{world, texturePath}, m_MoveVelocity{velocity}, m_LeftShift{0.f}, m_TopShift {0.f}
	{
		const auto windowSize = world->GetWindowSize();
		GetSprite().setOrigin(0.f, 0.f);
		GetSprite().setTextureRect(sf::IntRect(sf::Vector2i {0, 0}, sf::Vector2i {(int)windowSize.x, (int)windowSize.y}));
		SetTextureRepeated(true);
	}

	void BackdropActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		
		m_LeftShift += deltaTime * m_MoveVelocity.x;
		m_TopShift += deltaTime * m_MoveVelocity.y;

		sf::IntRect currentRect = GetSprite().getTextureRect();
		currentRect.left = m_LeftShift;
		currentRect.top = m_TopShift;

		GetSprite().setTextureRect(currentRect);
	}
}