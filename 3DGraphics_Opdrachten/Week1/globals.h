#pragma once
// https://stackoverflow.com/questions/33971318/the-correct-way-of-returning-stdunique-ptr-to-an-object-of-polymorphic-class
struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() :x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) :x(x), y(y), z(z) {}
};