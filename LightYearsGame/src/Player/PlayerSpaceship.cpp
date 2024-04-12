#include <SFML/System.hpp>
#include <Utility/Math.h>
#include "Player/PlayerSpaceship.h"

PlayerSpaceship::PlayerSpaceship(ly::World* world, const std::string& filepath)
	: Spaceship{world, filepath}, m_MoveInput{0, 0}, m_Speed{200.f}
{
}

void PlayerSpaceship::Tick(float deltaTime)
{
	Spaceship::Tick(deltaTime);
	HandleInput();
	ConsumeInput(deltaTime);
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
}

void PlayerSpaceship::ConsumeInput(float deltaTime)
{
	SetVelocity(m_MoveInput * m_Speed);
	m_MoveInput.x = m_MoveInput.y = 0.f;
}

void PlayerSpaceship::NormalizeInput()
{
	ly::Math::Normalize(m_MoveInput);
}

void PlayerSpaceship::ClampInputToScreenEdge()
{
	const sf::Vector2f location = GetActorLocation();

	if ((location.x < 0.f && m_MoveInput.x == -1.f) || (location.x > GetWindowSize().x && m_MoveInput.x == 1.f))
		m_MoveInput.x = 0;
	if ((location.y < 0.f && m_MoveInput.y == -1.f) || (location.y > GetWindowSize().y && m_MoveInput.y == 1.f))
		m_MoveInput.y = 0;
}
