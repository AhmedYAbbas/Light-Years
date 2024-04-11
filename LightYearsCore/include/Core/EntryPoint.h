#pragma once

#include "Framework/Application.h"

int main()
{
	const auto app = ly::CreateApplication();
	app->Run();
	delete app;
}