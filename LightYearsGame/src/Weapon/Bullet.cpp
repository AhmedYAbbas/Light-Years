#include "Weapon/Bullet.h"

namespace ly
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		: Actor{world, texturePath}, m_Owner{owner}, m_Speed{speed}, m_Damage{damage}
	{
	}

	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		Move(deltaTime);
	}

	void Bullet::Move(float deltaTime)
	{
		AddActorLocationOffset(-GetRightDirection() * m_Speed * deltaTime);
	}
}
