#pragma once
#include "Renderer.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Ray.hpp"

class	Application
{
	public:
		Application(void);
		~Application(void);
		Application(const Application &other) = delete;
		Application	&operator=(const Application &other) = delete;

		void	run(void);

	private:
		Renderer	*_renderer;
		Texture		*_canvas;
};
