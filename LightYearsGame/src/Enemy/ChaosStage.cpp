#include <Framework/World.h>
#include <Utility/Math.h>

#include "Enemy/ChaosStage.h"
#include "Enemy/Vanguard.h"
#include "Enemy/TwinBlade.h"
#include "Enemy/Hexagon.h"
#include "Enemy/UFO.h"

namespace ly
{
	ChaosStage::ChaosStage(World* world)
		: GameStage{world},
		m_SpawnInterval{4.f},
		m_MinSpawnInterval{0.8f},
		m_SpawnIntervalDecrement{0.5f},
		m_SpawnIntervalDecrementInterval{5.f},
		m_StageDuration{60.f}
	{
	}

	void ChaosStage::StartStage()
	{
		m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, m_SpawnInterval);
		m_DifficultyTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::IncreaseDifficulty, m_SpawnIntervalDecrementInterval, true);
		TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, m_StageDuration);
	}

	void ChaosStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(m_DifficultyTimerHandle);
		TimerManager::Get().ClearTimer(m_SpawnTimer);
	}

	void ChaosStage::SpawnVanguard()
	{
		WeakRef<Vanguard> vanguard = GetWorld()->SpawnActor<Vanguard>();
		vanguard.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade, m_SpawnInterval);
	}

	void ChaosStage::SpawnTwinBlade()
	{
		WeakRef<TwinBlade> twinBlade = GetWorld()->SpawnActor<TwinBlade>();
		twinBlade.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexagon, m_SpawnInterval);
	}

	void ChaosStage::SpawnHexagon()
	{
		WeakRef<Hexagon> hexagon = GetWorld()->SpawnActor<Hexagon>();
		hexagon.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO, m_SpawnInterval);
	}

	void ChaosStage::SpawnUFO()
	{

		const sf::Vector2f spawnLocation = GetRandomSpawnLocationSide();
		const auto windowSize = GetWorld()->GetWindowSize();
		const sf::Vector2f center = sf::Vector2f {windowSize.x / 2.f, windowSize.y / 2.f};
		sf::Vector2f direction = center - spawnLocation;
		Math::Normalize(direction);

		WeakRef<UFO> ufo = GetWorld()->SpawnActor<UFO>(direction * 200.f);
		ufo.lock()->SetActorLocation(spawnLocation);

		m_SpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, m_SpawnInterval);
	}

	void ChaosStage::IncreaseDifficulty()
	{
		m_SpawnInterval -= m_SpawnIntervalDecrement;
		if (m_SpawnInterval < m_MinSpawnInterval)
			m_SpawnInterval = m_MinSpawnInterval;
	}

	void ChaosStage::StageDurationReached()
	{
		FinishStage();
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
	{
		const auto windowSize = GetWorld()->GetWindowSize();
		const float spawnX = Math::RandomRange(100.f, windowSize.x - 100.f);
		const float spawnY = -100.f;

		return {spawnX, spawnY};
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationSide() const
	{
		const auto windowSize = GetWorld()->GetWindowSize();
		const float spawnLeft = Math::RandomRange(-1.f, 1.f);
		float xSpawnLocation = 0;
		if (spawnLeft < 0)
			xSpawnLocation = windowSize.x + 100.f;
		else
			xSpawnLocation = -100.f;

		const float ySpawnLocation = Math::RandomRange(0, windowSize.y);
		return sf::Vector2f {xSpawnLocation, ySpawnLocation};
	}
}