#include "../inc/Application.hpp"

//static Uint32	normal_shading(AHittable::Hit hit);

Application::Application(void) : _renderer(nullptr), _canvas(nullptr)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
		throw (std::runtime_error("Unable to initialize SDL"));

	try
	{
		Window::getInstance();
	}
	catch (std::exception)
	{
		throw ;
	}

	try
	{
		_renderer = new Renderer(Window::getInstance());
		_canvas = new Texture(_renderer);
	}
	catch (std::exception)
	{
		throw ;
	}
}

Application::~Application(void)
{
	delete _canvas;
	try
	{
		Window::getInstance()->~Window();
	}
	catch (std::exception)
	{
	}
	SDL_Quit();
}

void	Application::run(void)
{
	Scene	scene = Scene();
	Quaternion right(5, Vec3(0, -1, 0));
	Quaternion left(5, Vec3(0, 1, 0));
	Quaternion up(5, Vec3(1, 0, 0));
	Quaternion down(5, Vec3(-1, 0, 0));
	while (true)
	{
		SDL_Event event;
		bool to_render = true;
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
					|| event.type == SDL_EVENT_QUIT)
				return ;
			if (event.type == SDL_EVENT_KEY_DOWN)
			{
				to_render = true;
				switch (event.key.key)
				{
					case (SDLK_RIGHT):
						scene.getCam()->rotate(right);
						break ;
					case (SDLK_LEFT):
						scene.getCam()->rotate(left);
						break ;
					case (SDLK_UP):
						scene.getCam()->rotate(up);

						break ;
					case (SDLK_DOWN):
						scene.getCam()->rotate(down);
				}
			}
		}
		if (to_render)
		{
			scene.render(_canvas);
			to_render = false;
		}
		SDL_Delay(16);
	}
}
/*
static Uint32	normal_shading(AHittable::Hit hit)
{
	float	x = (hit.normal.x + 1.0f) * 0.5f;
	float	y = (hit.normal.y + 1.0f) * 0.5f;
	float	z = (hit.normal.z + 1.0f) * 0.5f;

	Uint8 red = static_cast<Uint8>(255.0f * x);
	Uint8 green = static_cast<Uint8>(255.0f * y);
	Uint8 blue = static_cast<Uint8>(255.0f * z);
	return (red << 24 | green << 16 | blue << 8 | 255);
}*/
