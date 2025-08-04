#include "../inc/raytracer.h"

Texture	*initialize_sdl(void)
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
	Texture	*ret = nullptr;
	try
	{
		Renderer rend = Renderer(Window::getInstance());
		ret = new Texture(rend);
	}
	catch (std::exception)
	{
		throw ;
	}
	return (ret);
}
