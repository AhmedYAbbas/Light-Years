#include <SFML/System.hpp>
#include <Utility/Math.h>

#include "Player/PlayerSpaceship.h"
#include "Weapon/ThreeWayShooter.h"
#include "Weapon/FrontalWiper.h"

namespace ly
{
	PlayerSpaceship::PlayerSpaceship(World* world, const std::string& filepath)
		: Spaceship {world, filepath},
		m_MoveInput {0, 0},
		m_Speed {200.f},
		m_Shooter {CreateScope<BulletShooter>(this, 0.5f, sf::Vector2f{50.f, 0.f})},
		m_InvulnerableTime {2.f},
		m_Invulnerable {true},
		m_InvulnerableFlashInterval {0.5f},
		m_InvulnerableFlashTimer {0.f},
		m_InvulnerableFlashDirection {1.f}
	{
		SetTeamID(1);
		m_Shooter->SetCurrentLevel(4);
	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
		UpdateInvulnerable(deltaTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (m_Shooter)
			m_Shooter->Shoot();
	}

	void PlayerSpaceship::TakeDamage(float amount)
	{
		if (!m_Invulnerable)
			Spaceship::TakeDamage(amount);
	}

	void PlayerSpaceship::SetShooter(Scope<Shooter> shooter)
	{
		if (m_Shooter && typeid(*m_Shooter) == typeid(*shooter))
		{
			m_Shooter->IncrementLevel();
			return;
		}

		m_Shooter = std::move(shooter);
	}

	void PlayerSpaceship::BeginPlay()
	{
		Spaceship::BeginPlay();
		TimerManager::Get().SetTimer(GetWeakRef(), &PlayerSpaceship::StopInvulnerable, m_InvulnerableTime);
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			m_MoveInput.y = -1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			m_MoveInput.y = 1.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_MoveInput.x = -1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_MoveInput.x = 1.f;

		ClampInputToScreenEdge();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			Shoot();
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		SetVelocity(m_MoveInput * m_Speed);
		m_MoveInput.x = m_MoveInput.y = 0.f;
	}

	void PlayerSpaceship::NormalizeInput()
	{
		Math::Normalize(m_MoveInput);
	}

	void PlayerSpaceship::ClampInputToScreenEdge()
	{
		const sf::Vector2f location = GetActorLocation();

		if ((location.x < 0.f && m_MoveInput.x == -1.f) || (location.x > GetWindowSize().x && m_MoveInput.x == 1.f))
			m_MoveInput.x = 0;
		if ((location.y < 0.f && m_MoveInput.y == -1.f) || (location.y > GetWindowSize().y && m_MoveInput.y == 1.f))
			m_MoveInput.y = 0;
	}

	void PlayerSpaceship::StopInvulnerable()
	{
		GetSprite().setColor({255, 255, 255});
		m_Invulnerable = false;
	}

	void PlayerSpaceship::UpdateInvulnerable(float deltaTime)
	{
		if (!m_Invulnerable)
			return;

		m_InvulnerableFlashTimer += deltaTime * m_InvulnerableFlashDirection;
		if (m_InvulnerableFlashTimer < 0 || m_InvulnerableFlashTimer > m_InvulnerableFlashInterval)
			m_InvulnerableFlashDirection *= -1;

		GetSprite().setColor(Math::Lerp({255, 255, 255, 64}, {255, 255, 255, 128}, m_InvulnerableFlashTimer / m_InvulnerableFlashInterval));
	}

}