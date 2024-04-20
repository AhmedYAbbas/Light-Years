#include <random>
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

	float Math::Lerp(float a, float b, float t)
	{
		if (t > 1.f)	t = 1.f;
		if (t < 0.f)	t = 0.f;

		return a + (b - a) * t;
	}

	sf::Color Math::Lerp(const sf::Color& a, const sf::Color& b, float t)
	{
		int colorR = Lerp(a.r, b.r, t);
		int colorG = Lerp(a.g, b.g, t);
		int colorB = Lerp(a.b, b.b, t);
		int colorA = Lerp(a.a, b.a, t);

		return sf::Color(colorR, colorG, colorB, colorA);
	}

	sf::Vector2f Math::Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t)
	{
		float x = Lerp(a.x, b.x, t);
		float y = Lerp(a.y, b.y, t);

		return sf::Vector2f(x, y);
	}

	float Math::RandomRange(float min, float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<float> distribution(min, max);

		return distribution(gen);
	}

	sf::Vector2f Math::RandomUnitVector()
	{
		float x = RandomRange(-1.f, 1.f);
		float y = RandomRange(-1.f, 1.f);
		sf::Vector2f randomVec(x, y);
		Normalize(randomVec);

		return randomVec;
	}
}