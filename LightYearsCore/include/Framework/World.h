#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Core.h"
#include "Framework/Object.h"

namespace ly
{
	class Actor;
	class Application;
	class GameStage;

	class World : public Object
	{
	public:
		World();
		virtual ~World() = default;

		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		template<typename T, typename ...Args>
		WeakRef<T> SpawnActor(Args&& ...args)
		{
			Ref<T> actor = CreateRef<T>(this, std::forward<Args>(args)...);
			m_PendingActors.push_back(actor);
			return actor;
		}

		sf::Vector2u GetWindowSize() const;
		void CleanCycle();
		void AddStage(const Ref<GameStage>& stage);

	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void InitGameStages();
		virtual void AllGameStagesFinished();

		void NextGameStage();
		void StartStages();
		
	private:
		Vector<Ref<GameStage>> m_GameStages;
		Vector<Ref<GameStage>>::iterator m_CurrentStage;

		Vector<Ref<Actor>> m_Actors;
		Vector<Ref<Actor>> m_PendingActors;
		bool m_HasBegunPlay;
	};
}