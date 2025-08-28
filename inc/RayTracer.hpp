#pragma once
#include <memory>
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

		void	render(std::shared_ptr<Canvas> target, std::shared_ptr<Scene> sc);

	private:
		ThreadPool	&_pool;
		int			_max_depth;
};
