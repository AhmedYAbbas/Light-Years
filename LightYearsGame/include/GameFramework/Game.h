#pragma once

#include <LightYears.h>

class Game : public ly::Application
{
public:
	Game();

	virtual void Render() override;
	virtual void Tick(float deltaTime) override;

private:
	float counter = 0.f;
	WeakRef<ly::Actor> actorToDestroy;
};