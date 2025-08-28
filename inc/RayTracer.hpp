#pragma once
#include <memory>
#include "Canvas.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

class	RayTracer
{
	public:
		RayTracer(void) = delete;
		RayTracer(const Camera &cam, const Scene &sc);
		RayTracer(const RayTracer &other) = delete;
		RayTracer	&operator=(const RayTracer &other) = delete;

		void	render(std::shared_ptr<Canvas> target, ThreadPool &pool);

	private:
		const Camera	&_cam;
		const Scene		&_sc;
		int				_max_depth;
};
