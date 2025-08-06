#pragma once
#include "Vec3.hpp"
#include "Window.hpp"

class	Camera
{
	public:
		Camera(void) = delete;
		Camera(float fov_degrees, Vec3 origin, Vec3 direction);
		~Camera(void) = default;
		Camera(const Camera &other);
		Camera	&operator=(const Camera &other);

	private:
		float	_fov_rad;
		Vec3	_orig;
		Vec3	_dir;
		Vec3	_delta_u;
		Vec3	_delta_v;
		Vec3	_pixel_zero;
};
