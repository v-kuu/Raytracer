#include <SDL3/SDL.h>
#include <iostream>
#include "../inc/raytracer.h"

int	main(void)
{
	Texture *canvas = nullptr;
	try
	{
		canvas = initialize_sdl();
		run_event_loop(canvas);
	}
	catch (std::exception &e)
	{
		std::cerr << "Raytracer error: " << e.what() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
	}
	delete canvas;
	try
	{
		Window::getInstance()->~Window();
	}
	catch (std::exception)
	{
	}
	SDL_Quit();
	return (0);
}
