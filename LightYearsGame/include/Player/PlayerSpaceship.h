#pragma once

#include "Spaceship/Spaceship.h"

class PlayerSpaceship : public Spaceship
{
public:
	PlayerSpaceship(ly::World* world, const std::string& filepath = "SpaceShooterRedux/PNG/playerShip1_blue.png");

	virtual void Tick(float deltaTime) override;
	inline void SetSpeed(float speed) { m_Speed = speed; }
	inline float GetSpeed() const { return m_Speed; }

private:
	void HandleInput();
	void ConsumeInput(float deltaTime);
	void NormalizeInput();
	void ClampInputToScreenEdge();

private:
	sf::Vector2f m_MoveInput;
	float m_Speed;
};