#include "../inc/Vec2.hpp"

Vec2::Vec2(void) : x(0), y(0)
{
}

Vec2::Vec2(float x, float y) : x(x), y(y)
{
}

Vec2	Vec2::operator+(const Vec2 &other) const
{
	return (Vec2(x + other.x, y + other.y));
}

Vec2	Vec2::operator-(const Vec2 &other) const
{
	return (Vec2(x - other.x, y - other.y));
}

Vec2	Vec2::operator*(float scalar) const
{
	return (Vec2(x * scalar, y * scalar));
}

//component wise multiplication
Vec2	Vec2::operator*(const Vec2 &other) const
{
	return (Vec2(x * other.x, y * other.y));
}

Vec2	Vec2::operator/(float scalar) const
{
	return (Vec2(x / scalar, y / scalar));
}

float&	Vec2::operator[](unsigned int i)
{
	switch (i)
	{
		case (0):
			return (x);
		case (1):
			return (y);
		default:
			throw (std::runtime_error("Vec2 index out of bounds"));
	}
}

const float&	Vec2::operator[](unsigned int i) const
{
	switch (i)
	{
		case (0):
			return (x);
		case (1):
			return (y);
		default:
			throw (std::runtime_error("Vec2 index out of bounds"));
	}
}

float	Vec2::length(void) const
{
	return (sqrtf(x * x + y * y));
}

Vec2	Vec2::normalize(void) const
{
	return (*this / this->length());
}

std::ostream	&operator<<(std::ostream &os, const Vec2 &vec)
{
	os << "{" << vec.x << ", " << vec.y << "}";
	return (os);
}
