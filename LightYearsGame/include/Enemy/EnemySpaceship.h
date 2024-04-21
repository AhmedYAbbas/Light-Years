#pragma once

#include "Spaceship/Spaceship.h"

namespace ly
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* world, const std::string& texturePath, float collisionDamage = 200.f);

	protected:
		virtual void Tick(float deltaTime) override;

	private:
		virtual void OnActorBeginOverlap(Actor* other) override;

	private:
		float m_CollisionDamage;
	};
}