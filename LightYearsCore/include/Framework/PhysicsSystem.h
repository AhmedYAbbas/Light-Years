#pragma once

#include <box2d/b2_world.h>

#include "Core/Core.h"

namespace ly
{
	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get() const;

	protected:
		PhysicsSystem();

	private:
		b2World m_PhysicsWorld;
		float m_PhysicsScale;

	private:
		static Scope<PhysicsSystem> s_Instance;
	};
}