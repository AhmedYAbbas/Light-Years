#pragma once

#include <SFML/Graphics.hpp>

namespace ly
{
	class Math
	{
	public:
		static sf::Vector2f RotationToVector(float rotation);
		static float DegToRad(float degrees);
		static float RadToDeg(float radians);
	};
}