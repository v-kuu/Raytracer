#pragma once
#include <memory>
#include "Renderer.hpp"
#include "Canvas.hpp"
#include "Scene.hpp"
#include "ThreadPool.hpp"
#include "RayTracer.hpp"

class	Application
{
	public:
		Application(void);
		~Application(void);
		Application(const Application &other) = delete;
		Application	&operator=(const Application &other) = delete;

		void	run(void);

	private:
		std::shared_ptr<Renderer> _renderer;
		std::unique_ptr<Canvas> _canvas;
};
