#pragma once
#include <string>
#include <random>
class Vec2f;
namespace Util
{
	struct Color4
	{
		float r, g, b, a;
		Color4(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	};
	std::string getExePath();
	void drawText(const Color4& clr, const Vec2f& pos, int windowWidth, int windowHeight, const std::string& text);
	template<typename T>
	T getRandomNumber(T min, T max)
	{
		static thread_local std::mt19937 rng;
		std::uniform_int_distribution<T> distributor(min, max);
		return distributor(rng);
	}

	void toTime(int ms, int* minutes, int* seconds);
}