#pragma once

#include <box2d/b2_world.h>

#include "Core/Core.h"

namespace ly
{
	class Actor;

	class PhysicsContactListener : public b2ContactListener
	{
	public:
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};

	class PhysicsSystem
	{
	public:
		static PhysicsSystem& Get();
		void Step(float timeStep);
		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* body);

		inline float GetPhysicsScale() const { return m_PhysicsScale; }
		
		static void Cleanup();

	protected:
		PhysicsSystem();

	private:
		void ProcessPendingRemoveListeners();

	private:
		b2World m_PhysicsWorld;
		float m_PhysicsScale;
		int m_VelocityIterations;
		int m_PositionIterations;
		
		PhysicsContactListener m_ContactListener;

		Set<b2Body*> m_PendingRemoveListeners;

	private:
		static Scope<PhysicsSystem> s_Instance;
	};
}