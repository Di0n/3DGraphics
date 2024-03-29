#include "Vec.h"

Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3f::Vec3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}
Vec3f::Vec3f(const Vec3f &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& Vec3f::operator [](int index)
{
	return v[index];
}

Vec3f Vec3f::operator-(const Vec3f & other)
{
	return Vec3f(x - other.x, y - other.y, z - other.z);
}

Vec3f Vec3f::operator+(const Vec3f& v) const
{
	return Vec3f(x + v.x, y + v.y, z + v.z);
}
Vec3f& Vec3f::operator+=(const Vec3f& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vec3f Vec3f::operator*(float f) const
{
	return Vec3f(x * f, y * f, z * f);
}

Vec3f& Vec3f::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}
Vec3f Vec3f::operator-() const
{
	return Vec3f(x, y, z) * -1;
}

Vec3f Vec3f::normalized() const
{
	float len = length();
	return Vec3f(x / len, y / len, z / len);
}

float Vec3f::length() const
{
	return sqrtf(x*x+y*y+z*z);
}

float Vec3f::distance(const Vec3f& v) const
{
	Vec3f diff;
	diff.x = x - v.x;
	diff.y = y - v.y;
	diff.z = z - v.z;

	return sqrtf(powf(diff.x, 2) + powf(diff.y, 2) + powf(diff.z, 2));
}



Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}
Vec2f::Vec2f(const Vec2f &other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](int index)
{
	return v[index];
}
