#pragma once
#include <math.h>
struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() :x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) :x(x), y(y), z(z) {}

	Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3& operator+=(const Vector3& v)
	{
		x += v.x;
		x += v.y;
		x += v.z;

		return *this;
	}

	Vector3 operator*(float f) const
	{
		return Vector3(x * f, y * f, z * f);
	}

	Vector3& operator*=(float f)
	{
		x = x * f;
		y = y * f;
		z = z * f;

		return *this;
	}

	Vector3 operator-() const
	{
		return (Vector3(x, y, z) * -1);
	}

	Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	float Magnitude() const
	{
		return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
	}

	Vector3 Normalize() const
	{
		const float magnitude = this->Magnitude();
		return Vector3(x / magnitude, y / magnitude, z / magnitude);
	}

	float Dot(const Vector3& v) const
	{
		return (x * v.x) + (y * v.y) + (z * v.z);
	}

	static Vector3 Zero()
	{
		return Vector3(0, 0, 0);
	}
};