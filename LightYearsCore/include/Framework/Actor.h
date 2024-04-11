#pragma once

#include "Core/Core.h"
#include "Framework/Object.h"

namespace ly
{
	class World;

	class Actor : public Object
	{
	public:
		Actor(World* world);
		virtual ~Actor();

		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		inline World* GetWorld() const { return m_World; }

	private:
		void BeginPlayInternal();
		void TickInternal(float deltaTime);

	private:
		World* m_World;
		bool m_HasBegunPlay;
	};
}