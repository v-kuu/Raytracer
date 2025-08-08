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
	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_QUIT)
				return ;
		}
		scene.render(_canvas);
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
