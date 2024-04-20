#pragma once

#include "Framework/Actor.h"

namespace ly
{
	class Particle : public Actor
	{
	public:
		Particle(World* world, const std::string& filepath = "");

		void RandomVelocity(float min, float max);
		void RandomSize(float min, float max);
		void RandomLifeTime(float min, float max);

	protected:
		virtual void Tick(float deltaTime) override;

	private:
		void Move(float deltaTime);
		void Fade(float deltaTime);

	private:
		sf::Vector2f m_Velocity;
		float m_LifeTime;
		sf::Clock m_Timer;
	};
}