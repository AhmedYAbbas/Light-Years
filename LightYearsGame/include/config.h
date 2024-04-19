#pragma once

#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG
	return "assets/";
#else
	return "E:/dev/LightYears/LightYearsGame/assets/";
#endif // NDEBUG
}
