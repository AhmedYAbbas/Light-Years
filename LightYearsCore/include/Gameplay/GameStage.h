#pragma once

#include "Framework/Object.h"
#include "Framework/Delegate.h"

namespace ly
{
	class World;

	class GameStage : public Object
	{
	public:
		GameStage(World* world);

		inline const World* GetWorld() const { return m_World; }
		inline World* GetWorld() const { return m_World; }

		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		void FinishStage();
		inline bool IsStageFinished() const { return m_StageFinished; }

	private:
		virtual StageFinished();

	public:
		Delegate<> OnStageFinished;

	private:
		World* m_World;
		bool m_StageFinished;
	};
}