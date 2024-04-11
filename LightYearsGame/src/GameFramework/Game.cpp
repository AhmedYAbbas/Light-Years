#include <LightYears.h>
#include "GameFramework/Game.h"

ly::Application* ly::CreateApplication()
{
	return new Game();
}