#include "../inc/Camera.hpp"

Camera::Camera(float fov_degrees, Vec3 origin, Vec3 direction)
{
	_fov_rad = fov_degrees * (M_PI / 180);
	_orig = origin;
	_dir = direction.normalize();

	int width, height;
	if (!SDL_GetWindowSizeInPixels
			(Window::getInstance()->getWindow(), &width, &height))
		throw (std::runtime_error("Failed to get window size"));

	_orientation = Quaternion(Vec3(0, 0, -1), _dir).normalize();
	_delta_u = _orientation.rotate(Vec3(1, 0, 0));
	_delta_v = _orientation.rotate(Vec3(0, -1, 0));
	float focal_length = (static_cast<float>(width) / 2) / (tan(_fov_rad / 2));
	Vec3 center = (_dir * focal_length) + _orig;
	Vec3 upper_left = center - (_delta_v * height / 2) - (_delta_u * width / 2);
	_pixel_zero = upper_left + ((_delta_u + _delta_v) * 0.5f);
}

Camera::Camera(const Camera &other) : _fov_rad(other._fov_rad), _orig(other._orig),
	_dir(other._dir), _orientation(other._orientation), _delta_u(other._delta_u),
	_delta_v(other._delta_v), _pixel_zero(other._pixel_zero)
{
}

Camera&	Camera::operator=(const Camera &other)
{
	_fov_rad = other._fov_rad;
	_orig = other._orig;
	_dir = other._dir;
	_orientation = other._orientation;
	_delta_u = other._delta_u;
	_delta_v = other._delta_v;
	_pixel_zero = other._pixel_zero;
	return (*this);
}

Ray	Camera::pixelRay(int x, int y) const
{
	Vec3 pixel_center = _pixel_zero + (_delta_u * x + _delta_v * y);
	return (Ray(_orig, pixel_center - _orig));
}
