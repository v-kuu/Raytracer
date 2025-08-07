#include "../inc/Application.hpp"

//static Uint32	normal_shading(AHittable::Hit hit);
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

	int		w, h;
	if (!SDL_GetWindowSizeInPixels(Window::getInstance()->getWindow(), &w, &h))
	{
		throw (std::runtime_error("Failed to get texture size"));
	}

	// Temporary scene
	Camera	cam = Camera(90, Vec3(0, 0, 0), Vec3(0, 0, -1));
	BlinnPhongMaterial	mat = BlinnPhongMaterial(255, 126, 126);
	Sphere	sp = Sphere(2, Vec3(0, 0, -5), mat);
	PointLight L = PointLight(255, 255, 255, 1.0f, Vec3(-5, 10, -5));

	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_QUIT)
				return ;
		}
		if (!SDL_LockTexture(_canvas->getTexture(), NULL, &pixels, &pitch))
			throw (std::runtime_error("Could not lock SDL texture"));
		pixel_buffer = static_cast<Uint32*>(pixels);
		for (int y = 0; y < h; ++y)
		{
			for (int x = 0; x < w; ++x)
			{
				Ray	ray = cam.pixelRay(x, y);
				AHittable::Hit	hit = sp.detectHit(ray);
				if (hit.t >= 0)
					//pixel_color = normal_shading(hit);
					pixel_color = sp.getMat().shade(ray, hit, L);
				else
					pixel_color = skybox(ray);
				pixel_buffer[y * (pitch / sizeof(Uint32)) + x] = pixel_color;
			}
		}
		SDL_UnlockTexture(_canvas->getTexture());
		SDL_RenderClear(_renderer->getRenderer());
		SDL_RenderTexture(_renderer->getRenderer(), _canvas->getTexture(), NULL, NULL);
		SDL_RenderPresent(_renderer->getRenderer());
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

static Uint32	skybox(Ray ray)
{
	Vec3 unit_dir = ray.dir.normalize();
	float fraction = 0.5 * (-unit_dir.y + 1.0f);
	Uint8 red = (0xFF - 0x77) * fraction + (0x77);
	Uint8 green = (0xFF - 0xBB) * fraction + (0xBB);
	Uint8 blue = (0xFF - 0xFF) * fraction + (0xFF);
	return (red << 24 | green << 16 | blue << 8 | 0xFF);
}
