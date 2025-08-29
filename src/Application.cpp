#include "../inc/Application.hpp"

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
		_renderer = std::make_shared<Renderer>(Window::getInstance());
		_canvas = std::make_unique<Canvas>(_renderer);
	}
	catch (std::exception)
	{
		throw ;
	}
}

Application::~Application(void)
{
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
	std::shared_ptr<Scene> scene = std::make_shared<Scene>();
	ThreadPool	pool = ThreadPool(6);
	RayTracer rt(pool, 1);
	Vec3 mov;
	SDL_Event event;
	bool to_render = true;
	while (true)
	{
		float r_right = 0;
		float r_left = 0;
		float r_up = 0;
		float r_down = 0;
		Vec3 mov(0, 0, 0);
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
						r_right += 5;
						break ;
					case (SDLK_LEFT):
						r_left += 5;
						break ;
					case (SDLK_UP):
						r_up += 5;
						break ;
					case (SDLK_DOWN):
						r_down += 5;
						break ;
					case (SDLK_D):
						mov.x += 0.5f;
						break ;
					case (SDLK_A):
						mov.x -= 0.5f;
						break ;
					case (SDLK_W):
						mov.y += 0.5f;
						break ;
					case (SDLK_S):
						mov.y -= 0.5f;
						break ;
					case (SDLK_R):
						mov.z -= 0.5f;
						break ;
					case (SDLK_F):
						mov.z += 0.5f;
				}
			}
		}
		if (to_render)
		{
			Quaternion rot = (Quaternion(r_right, Vec3(0, -1 , 0))
					* Quaternion(r_left, Vec3(0, 1, 0))
					* Quaternion(r_up, Vec3(1, 0, 0))
					* Quaternion(r_down, Vec3(-1, 0, 0))).normalize();
			scene->getCam()->rotate(rot);
			scene->getCam()->translate(mov);
			scene->getCam()->update();
			rt.render(*_canvas, *scene);
			to_render = false;
		}
		SDL_Delay(16);
	}
}
