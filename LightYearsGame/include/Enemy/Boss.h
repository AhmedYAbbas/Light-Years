#pragma once

#include "Enemy/EnemySpaceship.h"

#include "Weapon/BulletShooter.h"
#include "Weapon/ThreeWayShooter.h"
#include "Weapon/FrontalWiper.h"

namespace ly
{
	class Boss : public EnemySpaceship
	{
	public:
		Boss(World* world);

	protected:
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;

	private:
		void CheckMovement();
		void ShootBaseShooter();
		void ShootThreeWayShooter();
		void ShootFrontalWiper();
		void SetStage(int stage);
		void OnHealthChanged(float amount, float health, float maxHealth);

	private:
		float m_Speed;
		float m_BaseSpeed;
		float m_SwitchDistanceToEdge;

		BulletShooter m_BaseShooterLeft;
		BulletShooter m_BaseShooterRight;
		
		ThreeWayShooter m_ThreeWayShooter;
		FrontalWiper m_FrontalWiperLeft;
		FrontalWiper m_FrontalWiperRight;

		BulletShooter m_FinalStageShooterLeft;
		BulletShooter m_FinalStageShooterRight;

		int m_Stage;
	};
}