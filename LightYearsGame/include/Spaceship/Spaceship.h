#pragma once

#include <Framework/Actor.h>

class Spaceship : public ly::Actor
{
public:
	Spaceship(ly::World* world, const std::string& filepath = "");

	virtual void Tick(float deltaTime) override;
	void SetVelocity(const sf::Vector2f& velocity);

	inline const sf::Vector2f& GetVelocity() const { return m_Velocity; }

private:
	sf::Vector2f m_Velocity;
};