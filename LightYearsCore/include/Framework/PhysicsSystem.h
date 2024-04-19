#pragma once

#include <box2d/b2_world.h>

#include "Core/Core.h"

namespace ly
{
	class Actor;

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();
		void Step(float timeStep);
		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* body);

		inline float GetPhysicsScale() const { return m_PhysicsScale; }

	protected:
		PhysicsSystem();

	private:
		b2World m_PhysicsWorld;
		float m_PhysicsScale;
		int m_VelocityIterations;
		int m_PositionIterations;

	private:
		static Scope<PhysicsSystem> s_Instance;
	};
}