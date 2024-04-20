#include <Utility/Math.h>

#include "VFX/Explosion.h"
#include "VFX/Particle.h"

namespace ly
{
	Explosion::Explosion(int particleAmount, float minLifeTime, float maxLifeTime, float minSize, float maxSize, float minSpeed, float maxSpeed, const sf::Color& particleColor, const Vector<std::string>& particlePaths)
		: m_ParticleAmount{particleAmount},
		m_MinLifeTime{minLifeTime},
		m_MaxLifeTime{maxLifeTime},
		m_MinSize{minSize},
		m_MaxSize{maxSize},
		m_MinSpeed{minSpeed},
		m_MaxSpeed{maxSpeed},
		m_ParticleColor{particleColor},
		m_ParticleImagePaths{particlePaths}
	{
	}

	void Explosion::SpawnExplosion(World* world, const sf::Vector2f& location)
	{
		for (int i = 0; i < m_ParticleAmount; ++i)
		{
			std::string particleImagePath = m_ParticleImagePaths[Math::RandomRange(0, m_ParticleImagePaths.size() - 1)];
			WeakRef<Particle> particle = world->SpawnActor<Particle>(particleImagePath);

			particle.lock()->RandomLifeTime(m_MinLifeTime, m_MaxLifeTime);
			particle.lock()->SetActorLocation(location);
			particle.lock()->RandomSize(m_MinSize, m_MaxSize);
			particle.lock()->RandomVelocity(m_MinSpeed, m_MaxSpeed);
			particle.lock()->GetSprite().setColor(m_ParticleColor);
		}
	}
}