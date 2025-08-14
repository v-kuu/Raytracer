#include "../inc/Quaternion.hpp"

Quaternion::Quaternion(void) : w(1), x(0), y(0), z(0)
{
}

Quaternion::Quaternion(float w, float x, float y, float z)
	: w(w), x(x), y(y), z(z)
{
}

Quaternion::Quaternion(float angle_deg, const Vec3 &axis)
{
	float angle_rad = angle_deg * (M_PI / 180);
	w = cos(angle_rad / 2);
	x = axis.x * sin(angle_rad / 2);
	y = axis.y * sin(angle_rad / 2);
	z = axis.z * sin(angle_rad / 2);
}

Quaternion::Quaternion(const Vec3 &from, const Vec3 &to)
{
	float dot_p = dot(from, to);
	if (dot_p < 1.0f)
	{
		Vec3 axis = cross(from, to);
		float angle = acosf(dot_p);
		w = cos(angle / 2);
		x = axis.x * sin(angle / 2);
		y = axis.y * sin(angle / 2);
		z = axis.z * sin(angle / 2);
	}
	else
	{
		w = 1.0f;
		x = 0;
		y = 0;
		z = 0;
	}
}

Quaternion	Quaternion::operator*(const Quaternion &other) const
{
	Vec3 first(x, y, z);
	Vec3 second(other.x, other.y, other.z);
	float scalar = w * other.w - dot(first, second);
	Vec3 vector = second * w + first * other.w + cross(first, second);
	return (Quaternion(scalar, vector.x, vector.y, vector.z));
}

bool	Quaternion::operator==(const Quaternion &other) const
{
	if (w == other.w && x == other.x && y == other.y && z == other.z)
		return (true);
	return (false);
}

Vec3	Quaternion::rotate(const Vec3 &other) const
{
	Vec3 vector(x, y, z);
	Vec3 ret = (vector * 2.0f * dot(vector, other)
			+ (other * (w * w - dot(vector, vector)))
			+ (cross(vector, other) * w * 2.0f));
	return (ret);
}

float	Quaternion::length(void) const
{
	return (sqrtf(w * w + x * x + y * y + z * z));
}

Quaternion	Quaternion::normalize(void) const
{
	float len = this->length();
	return (Quaternion(w / len, x / len, y / len, z / len));
}

Quaternion	Quaternion::inverse(void) const
{
	return (Quaternion(w, -x , -y, -z));
}

std::ostream	&operator<<(std::ostream &os, const Quaternion &quat)
{
	os << "{" << quat.w << ", " << quat.x << ", " << quat.y << ", " << quat.z
		<< "}";
	return (os);
}
