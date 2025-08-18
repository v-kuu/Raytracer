#pragma once
#include "Vec3.hpp"
#include "Quaternion.hpp"
#include "Window.hpp"
#include "Ray.hpp"
#include "AHittable.hpp"

class	Camera
{
	public:
		Camera(void) = delete;
		Camera(float fov_degrees, const Vec3 &origin, const Vec3 &direction);
		~Camera(void) = default;
		Camera(const Camera &other);
		Camera	&operator=(const Camera &other);

		Quaternion	getOrientation(void) const;

		Ray		pixelRay(int x, int y) const;
		void	translate(const Vec3 &mov);
		void	rotate(const Quaternion &quat);

	private:
		float		_fov_rad;
		Vec3		_orig;
		Vec3		_dir;
		Quaternion	_orientation;
		Vec3		_delta_u;
		Vec3		_delta_v;
		Vec3		_pixel_zero;
};

std::ostream	&operator<<(std::ostream &os, const Camera &cam);
