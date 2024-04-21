#include <Framework/World.h>
#include <Utility/Math.h>

#include "Enemy/UFOStage.h"
#include "Enemy/UFO.h"

namespace ly
{
	UFOStage::UFOStage(World* world)
		: GameStage{world}, m_SpawnInterval{4.f}, m_SpawnAmout{10}, m_CurrentSpawnAmout{0}, m_UFOSpeed{200.f}
	{
	}

	void UFOStage::StartStage()
	{
		GameStage::StartStage();
		m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, m_SpawnInterval, true);
	}

	void UFOStage::StageFinished()
	{
		GameStage::StageFinished();
		TimerManager::Get().ClearTimer(m_SpawnTimer);
	}

	void UFOStage::SpawnUFO()
	{
		const sf::Vector2f spawnLocation = GetRandomSpawnLocation();
		const auto windowSize = GetWorld()->GetWindowSize();
		const sf::Vector2f center {windowSize.x / 2.f, windowSize.y / 2.f};
		sf::Vector2f direction {center.x - spawnLocation.x, center.y - spawnLocation.y};
		Math::Normalize(direction);
		const sf::Vector2f velocity = direction * m_UFOSpeed;

		WeakRef<UFO> ufo = GetWorld()->SpawnActor<UFO>(velocity);
		ufo.lock()->SetActorLocation(spawnLocation);

		if (++m_CurrentSpawnAmout == m_SpawnAmout)
			FinishStage();
	}

	sf::Vector2f UFOStage::GetRandomSpawnLocation() const
	{
		const auto windowSize = GetWorld()->GetWindowSize();
		float spawnLeft = Math::RandomRange(-1.f, 1.f);
		float xSpawnLocation = 0;
		if (spawnLeft < 0)
			xSpawnLocation = windowSize.x + 100.f;
		else
			xSpawnLocation = -100.f;

		float ySpawnLocation = Math::RandomRange(0, windowSize.y);
		return sf::Vector2f {xSpawnLocation, ySpawnLocation};
	}
}