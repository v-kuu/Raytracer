#include "../inc/Application.hpp"

static Uint32	normal_shading(AHittable::Hit hit);
static Uint32	skybox(Ray ray);

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
	void	*pixels;
	Uint32	*pixel_buffer;
	int		pitch;
	Uint32	pixel_color;

	Camera	cam = Camera(90, Vec3(0, 0, 0), Vec3(0, 0, -1));
	Sphere	sp = Sphere(2, Vec3(0, 0, -5));

	while (true)
	{
		if (!SDL_LockTexture(_canvas->getTexture(), NULL, &pixels, &pitch))
			throw (std::runtime_error("Could not lock SDL texture"));
		pixel_buffer = static_cast<Uint32*>(pixels);
		//render frame
		int	x, y;
		if (!SDL_GetWindowSizeInPixels(Window::getInstance()->getWindow(), &x, &y))
		{
			throw (std::runtime_error("Failed to get texture size"));
		}
		for (int i = 0; i < y; ++i)
		{
			for (int j = 0; j < x; ++j)
			{
				Ray	ray = cam.pixelRay(j, i);
				AHittable::Hit	hit = sp.detectHit(ray);
				if (hit.t >= 0)
					pixel_color = normal_shading(hit);
				else
					pixel_color = skybox(ray);
				pixel_buffer[i * (pitch / sizeof(Uint32)) + j] = pixel_color;
			}
		}
		SDL_UnlockTexture(_canvas->getTexture());
		SDL_RenderClear(_renderer->getRenderer());
		SDL_RenderTexture(_renderer->getRenderer(), _canvas->getTexture(), NULL, NULL);
		SDL_RenderPresent(_renderer->getRenderer());
		SDL_Delay(2000);
		break ;
	}
}

static Uint32	normal_shading(AHittable::Hit hit)
{
	float	x = (hit.normal.x + 1.0f) * 0.5f;
	float	y = (hit.normal.y + 1.0f) * 0.5f;
	float	z = (hit.normal.z + 1.0f) * 0.5f;

	Uint8 red = static_cast<Uint8>(255.0f * x);
	Uint8 green = static_cast<Uint8>(255.0f * y);
	Uint8 blue = static_cast<Uint8>(255.0f * z);
	return (red << 24 | green << 16 | blue << 8 | 255);
}

static Uint32	skybox(Ray ray)
{
	Vec3 unit_dir = ray.dir.normalize();
	float fraction = 0.5 * (-unit_dir.y + 1.0f);
	Uint8 red = (0xFF - 0x77) * fraction + (0x77);
	Uint8 green = (0xFF - 0xBB) * fraction + (0xBB);
	Uint8 blue = (0xFF - 0xFF) * fraction + (0xFF);
	return (red << 24 | green << 16 | blue << 8 | 0xFF);
}
