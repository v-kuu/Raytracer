#include <SDL3/SDL.h>
#include <iostream>
#include "../inc/Application.hpp"

int	main(void)
{
	try
	{
		std::shared_ptr<Application> raytracer = std::make_shared<Application>();
		raytracer->run();
	}
	catch (std::exception &e)
	{
		std::cerr << "Raytracer error: " << e.what() << std::endl;
		std::cerr << SDL_GetError() << std::endl;
		return (1);
	}
	return (0);
}
