#include <SDL3/SDL.h>
#include <iostream>
#include "../inc/Application.hpp"

int	main(void)
{
	Application	*raytracer = nullptr;
	try
	{
		raytracer = new Application();
		raytracer->run();
	}
	catch (std::exception &e)
	{
		std::cerr << "Raytracer error: " << e.what() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
	}
	delete raytracer;
	return (0);
}
