#pragma once

#include <Framework/Actor.h>

namespace ly
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* world, const std::string& filepath = "");

		virtual void Tick(float deltaTime) override;
		void SetVelocity(const sf::Vector2f& velocity);

		inline const sf::Vector2f& GetVelocity() const { return m_Velocity; }
		virtual void Shoot();

	private:
		sf::Vector2f m_Velocity;
	};
}