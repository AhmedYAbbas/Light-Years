#include <Framework/World.h>

#include "Player/Player.h"
#include "Player/PlayerSpaceship.h"

namespace ly
{
	Player::Player()
		: m_LifeCount {3}, m_Score {0}
	{
	}

	WeakRef<PlayerSpaceship> Player::SpawnSpaceship(World* world)
	{
		if (m_LifeCount > 0)
		{
			--m_LifeCount;
			const auto windowSize = world->GetWindowSize();
			m_CurrentPlayerSpaceship = world->SpawnActor<PlayerSpaceship>();
			m_CurrentPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(windowSize.x / 2.f, windowSize.y - 100.f));
			OnLifeChanged.Broadcast(m_LifeCount);
			return m_CurrentPlayerSpaceship;
		}
		else
			OnLifeExhausted.Broadcast();

		return WeakRef<PlayerSpaceship>{};
	}

	void Player::AddLifeCount(unsigned int count)
	{
		if (count > 0)
		{
			m_LifeCount += count;
			OnLifeChanged.Broadcast(m_LifeCount);
		}
	}

	void Player::AddScore(unsigned int score)
	{
		if (score > 0)
		{
			m_Score += score;
			OnScoreChanged.Broadcast(m_Score);
		}
	}
}