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

		static float Lerp(float a, float b, float t);
		static sf::Color Lerp(const sf::Color& a, const sf::Color& b, float t);
		static sf::Vector2f Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t);

		float RandomRange(float min, float max);
		sf::Vector2f RandomUnitVector();

		template<typename T>
		static float GetVectorMagnitude(const sf::Vector2<T>& vector)
		{
			return std::sqrt(vector.x * vector.x + vector.y * vector.y);
		}

		template<typename T>
		static sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vector, float scale)
		{
			vector.x *= scale;
			vector.y *= scale;
			return vector;
		}

		template<typename T>
		static sf::Vector2<T>& Normalize(sf::Vector2<T>& vector)
		{
			float magnitude = GetVectorMagnitude<T>(vector);

			if (magnitude == 0.f)
				return vector;

			ScaleVector(vector, 1.f / magnitude);
			return vector;
		}
	};
}