#pragma once

#include <Framework/Object.h>
#include <Framework/Delegate.h>

namespace ly
{
	class PlayerSpaceship;
	class World;

	class Player : public Object
	{
	public:
		Player();

		WeakRef<PlayerSpaceship> SpawnSpaceship(World* world);

		inline const WeakRef<PlayerSpaceship> GetCurrentSpaceship() const { return m_CurrentPlayerSpaceship; }
		inline unsigned int GetLifeCount() const { return m_LifeCount; }
		inline unsigned int GetScore() const { return m_Score; }

		void AddLifeCount(unsigned int count);
		void AddScore(unsigned int score);

	public:
		Delegate<int> OnLifeChanged;
		Delegate<int> OnScoreChanged;
		Delegate<> OnLifeExhausted;

	private:
		unsigned int m_LifeCount;
		unsigned int m_Score;
		WeakRef<PlayerSpaceship> m_CurrentPlayerSpaceship;
	};
}