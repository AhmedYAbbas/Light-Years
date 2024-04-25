#include "Enemy/Boss.h"
#include "Gameplay/HealthComponent.h"

namespace ly
{
	Boss::Boss(World* world)
		: EnemySpaceship{world, "SpaceShooterRedux/PNG/Enemies/boss.png"},
		m_Speed{100.f},
		m_BaseSpeed{100.f},
		m_SwitchDistanceToEdge{100.f},
		m_BaseShooterLeft{this, 1.f, sf::Vector2f{50.f, -50.f}},
		m_BaseShooterRight{this, 1.f, sf::Vector2f{50.f, 50.f}},
		m_ThreeWayShooter{this, 4.f, sf::Vector2f{100.f, 0.f}},
		m_FrontalWiperLeft{this, 5.f, sf::Vector2f{80.f, -100.f}},
		m_FrontalWiperRight{this, 5.f, sf::Vector2f{80.f, 100.f}},
		m_FinalStageShooterLeft{this, 0.3f, sf::Vector2f{50.f, -150.f}},
		m_FinalStageShooterRight{this, 0.3f, sf::Vector2f{50.f, 150.f}},
		m_Stage{1}
	{
		SetActorRotation(180.f); 
		SetVelocity({m_Speed, 0.f});
		SetRewardSpawnWeight(0.f);
	}

	void Boss::BeginPlay()
	{
		EnemySpaceship::BeginPlay();

		HealthComponent& healthComponent = GetHealthComponent();
		healthComponent.SetInitialHealth(3000.f, 3000.f);
		healthComponent.OnHealthChanged.Bind(GetWeakRef(), &Boss::OnHealthChanged);
	}

	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);

		ShootBaseShooter();
		ShootFrontalWiper();
		ShootThreeWayShooter();

		if (m_Stage == 4)
		{
			m_FinalStageShooterLeft.Shoot();
			m_FinalStageShooterRight.Shoot();
		}

		CheckMovement();
	}

	void Boss::CheckMovement()
	{
		if (GetActorLocation().x > GetWindowSize().x - m_SwitchDistanceToEdge)
			SetVelocity({-m_Speed, 0.f});
		else if (GetActorLocation().x < m_SwitchDistanceToEdge)
			SetVelocity({m_Speed, 0.f});
	}

	void Boss::ShootBaseShooter()
	{
		m_BaseShooterLeft.Shoot();
		m_BaseShooterRight.Shoot();
	}

	void Boss::ShootThreeWayShooter()
	{
		m_ThreeWayShooter.Shoot();
	}

	void Boss::ShootFrontalWiper()
	{
		m_FrontalWiperLeft.Shoot();
		m_FrontalWiperRight.Shoot();
	}

	void Boss::SetStage(int stage)
	{
		m_Stage = stage;
		m_BaseShooterLeft.SetCurrentLevel(m_Stage);
		m_BaseShooterRight.SetCurrentLevel(m_Stage);
		m_FrontalWiperLeft.SetCurrentLevel(m_Stage);
		m_FrontalWiperRight.SetCurrentLevel(m_Stage);
		m_ThreeWayShooter.SetCurrentLevel(m_Stage);

		m_Speed = m_Stage * m_BaseSpeed;
	}

	void Boss::OnHealthChanged(float amount, float health, float maxHealth)
	{
		LOG("Health: %f/%f", health, maxHealth);
		
		float percentLeft = health / maxHealth;

		if (percentLeft < 0.7f && percentLeft > 0.5f)
			SetStage(2);
		if (percentLeft < 0.5f && percentLeft > 0.3f)
			SetStage(3);
		if (percentLeft < 0.3f)
			SetStage(4);
	}
}