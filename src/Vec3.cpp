#include "../inc/Vec3.hpp"

Vec3::Vec3(void) : x(0), y(0), z(0)
{
}

Vec3::Vec3(float xi, float yi, float zi) : x(xi), y(yi), z(zi)
{
}

Vec3	Vec3::operator+(const Vec3 &other) const
{
	return (Vec3(x + other.x, y + other.y, z + other.z));
}

Vec3	Vec3::operator-(const Vec3 &other) const
{
	return (Vec3(x - other.x, y - other.y, z - other.z));
}

Vec3	Vec3::operator*(float scalar) const
{
	return (Vec3(x * scalar, y * scalar, z * scalar));
}

Vec3	Vec3::operator/(float scalar) const
{
	return (Vec3(x / scalar, y / scalar, z / scalar));
}

float&	Vec3::operator[](unsigned int i)
{
	switch (i)
	{
		case (0):
			return (x);
		case (1):
			return (y);
		case (2):
			return (z);
		default:
			throw (std::runtime_error("Vec3 index out of bounds"));
	}
}

const float&	Vec3::operator[](unsigned int i) const
{
	switch (i)
	{
		case (0):
			return (x);
		case (1):
			return (y);
		case (2):
			return (z);
		default:
			throw (std::runtime_error("Vec3 index out of bounds"));
	}
}

float	Vec3::length(void) const
{
	return (sqrtf(x * x + y * y + z * z));
}

Vec3	Vec3::normalize(void) const
{
	return (*this / this->length());
}

std::ostream	&operator<<(std::ostream &os, const Vec3 &vec)
{
	os << "{" << vec.x << ", " << vec.y << ", " << vec.z << "}";
	return (os);
}

float	dot(const Vec3 &lhs, const Vec3 &rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

Vec3	cross(const Vec3 &lhs, const Vec3 &rhs)
{
	return (Vec3(lhs.y * rhs.z - lhs.z * rhs.y,
				lhs.z * rhs.x - lhs.x * rhs.z,
				lhs.x * rhs.y - lhs.y * rhs.x));
}
