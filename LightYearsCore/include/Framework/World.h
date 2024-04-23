#pragma once

#include <SFML/Graphics.hpp>

#include "Core/Core.h"
#include "Framework/Object.h"

namespace ly
{
	class HUD
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
		WeakRef<T> SpawnHUD(Args&& ...args)
		{
			Ref<T> HUD = CreateRef<T>(std::forward<Args>(args)...);
			m_HUD = HUD;
			return HUD;
		}
		
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
		bool DispatchEvent(const sf::Event& event);

	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void InitGameStages();
		virtual void AllGameStagesFinished();

		void RenderHUD(sf::RenderWindow& window);
		void NextGameStage();
		void StartStages();
		
	private:
		Vector<Ref<GameStage>> m_GameStages;
		Vector<Ref<GameStage>>::iterator m_CurrentStage;

		Vector<Ref<Actor>> m_Actors;
		Vector<Ref<Actor>> m_PendingActors;

		Ref<HUD> m_HUD;

		bool m_HasBegunPlay;
	};
}