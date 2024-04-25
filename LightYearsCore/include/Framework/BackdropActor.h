#pragma once

#include "Framework/Actor.h"

namespace ly
{
	class BackdropActor : public Actor
	{
	public:
		BackdropActor(World* world, const std::string& texturePath, const sf::Vector2f velocity = {0.f, -50.f});

	protected:
		virtual void Tick(float deltaTime) override;

	private:
		sf::Vector2f m_MoveVelocity;
		float m_LeftShift;
		float m_TopShift;
	};
}