#include "Utility/Math.h"

namespace ly
{
	const float PI = 3.1415926535;

	sf::Vector2f Math::RotationToVector(float rotation)
	{
		float radians = DegToRad(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	float Math::DegToRad(float degrees)
	{
		return degrees * (PI / 180.f);
	}

	float Math::RadToDeg(float radians)
	{
		return radians * (180.f / PI);
	}
}