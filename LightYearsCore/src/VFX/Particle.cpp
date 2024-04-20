#include "VFX/Particle.h"

namespace ly
{
	Particle::Particle(World* world, const std::string& filepath)
		: Actor{world, filepath}, m_Velocity{}, m_LifeTime{1.f}, m_Timer{}
	{
	}

	void Particle::RandomVelocity(float min, float max)
	{
		m_Velocity = Math::RandomUnitVector() * Math::RandomRange(min, max);
	}

	void Particle::RandomSize(float min, float max)
	{
		float randomScale = Math::RandomRange(min, max);
		GetSprite().setScale(randomScale, randomScale);
	}

	void Particle::RandomLifeTime(float min, float max)
	{
		m_LifeTime = Math::RandomRange(min, max);
	}

	void Particle::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		Move(deltaTime);
		Fade(deltaTime);

		if (m_Timer.getElapsedTime().asSeconds() >= m_LifeTime)
			Destroy();
	}

	void Particle::Move(float deltaTime)
	{
		AddActorLocationOffset(m_Velocity * deltaTime);
	}

	void Particle::Fade(float deltaTime)
	{
		float elapsedTime = m_Timer.getElapsedTime().asSeconds();
		GetSprite().setColor(Math::Lerp(GetSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime / m_LifeTime));
		GetSprite().setScale(Math::Lerp(GetSprite().getScale(), sf::Vector2f(0.f, 0.f), elapsedTime / m_LifeTime));
	}
}