#pragma once

#include <string>
#include <Core/Core.h>
#include <SFML/Graphics.hpp>

namespace ly
{
	class World;

	class Explosion
	{
	public:
		Explosion(int particleAmount = 20,
			float minLifeTime = 0.5f,
			float maxLifeTime = 1.5f,
			float minSize = 1.f,
			float maxSize = 3.f,
			float minSpeed = 200.f,
			float maxSpeed = 400.f,
			const sf::Color& particleColor = sf::Color{255, 128, 0, 255},
			const Vector<std::string>& particlePaths =
			{
				"SpaceShooterRedux/PNG/Effects/star1.png",
				"SpaceShooterRedux/PNG/Effects/star2.png",
				"SpaceShooterRedux/PNG/Effects/star3.png"
			}
		);

		void SpawnExplosion(World* world, const sf::Vector2f& location);

	private:
		int m_ParticleAmount;
		float m_MinLifeTime;
		float m_MaxLifeTime;
		float m_MinSize;
		float m_MaxSize;
		float m_MinSpeed;
		float m_MaxSpeed;
		sf::Color m_ParticleColor;

		Vector<std::string> m_ParticleImagePaths;
	};
}