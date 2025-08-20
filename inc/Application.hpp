#pragma once
#include <memory>
#include "Renderer.hpp"
#include "Canvas.hpp"
#include "Scene.hpp"
#include "ThreadPool.hpp"

class	Application
{
	public:
		Application(void);
		~Application(void);
		Application(const Application &other) = delete;
		Application	&operator=(const Application &other) = delete;

		void	run(void);

	private:
		std::shared_ptr<Renderer>	_renderer;
		std::shared_ptr<Canvas>	_canvas;
};
