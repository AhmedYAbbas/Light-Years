#include "Spaceship/Spaceship.h"

Spaceship::Spaceship(ly::World* world, const std::string& filepath)
	: Actor{world, filepath}
{
}

void Spaceship::Tick(float deltaTime)
{
	Actor::Tick(deltaTime);
	AddActorLocationOffset(GetVelocity() * deltaTime);
}

void Spaceship::SetVelocity(const sf::Vector2f& velocity)
{
	m_Velocity = velocity;
}
