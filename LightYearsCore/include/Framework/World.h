#pragma once

#include "Core/Core.h"

namespace ly
{
	class Actor;

	class World
	{
	public:
		World();
		virtual ~World() = default;

		void BeginPlay();
		void Tick(float deltaTime);

		template<typename T>
		WeakRef<T> SpawnActor()
		{
			Ref<T> actor = CreateRef<T>(this);
			m_PendingActors.push_back(actor);
			return actor;
		}

	private:
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		
	private:
		Vector<Ref<Actor>> m_Actors;
		Vector<Ref<Actor>> m_PendingActors;
		bool m_HasBegunPlay;
	};
}