#include "Framework/PhysicsSystem.h"

namespace ly
{
	Scope<PhysicsSystem> PhysicsSystem::s_Instance = nullptr;

	PhysicsSystem& ly::PhysicsSystem::Get() const
	{
		if (!s_Instance)
			s_Instance = CreateScope<PhysicsSystem>();

		return *s_Instance;
	}

	PhysicsSystem::PhysicsSystem()
		: m_PhysicsWorld{b2Vec2_zero}, m_PhysicsScale{0.01f}
	{
	}
}