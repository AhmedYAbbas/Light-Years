#pragma once

#include "Core/Core.h"

namespace ly
{
	class World;

	class Actor
	{
	public:
		Actor(World* world);
		virtual ~Actor() = default;

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		inline Ref<World> GetWorld() const { return m_World; }

	private:
		void BeginPlayInternal();
		void TickInternal(float deltaTime);

	private:
		Ref<World> m_World;
		bool m_HasBegunPlay;
	};
}