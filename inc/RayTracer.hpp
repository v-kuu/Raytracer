#pragma once
#include "Canvas.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "ThreadPool.hpp"
#include "SkyboxMaterial.hpp"

class	RayTracer
{
	public:
		RayTracer(void) = delete;
		RayTracer(ThreadPool &pool, int max_depth);
		RayTracer(const RayTracer &other) = delete;
		RayTracer	&operator=(const RayTracer &other) = delete;

		void	render(Canvas &target, Scene &sc);

	private:
		ThreadPool	&_pool;
		int			_max_depth;
};
