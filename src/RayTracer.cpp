#include "../inc/RayTracer.hpp"

RayTracer::RayTracer(ThreadPool &pool, int max_depth)
	: _pool(pool), _max_depth(max_depth)
{
}

void	RayTracer::render(Canvas &target, Scene &sc)
{
	(void)_max_depth;
	const Renderer &renderer = *target.getRenderer();
	const Camera &cam = *sc.getCam();
	SkyboxMaterial	skybox;
	void	*pixels;
	Uint32	*pixel_buffer;
	int		pitch, w, h;

	if (!SDL_GetWindowSizeInPixels(Window::getInstance()->getWindow(), &w, &h))
		throw (std::runtime_error("Failed to get texture size"));
	if (!SDL_LockTexture(target.getTexture(), NULL, &pixels, &pitch))
		throw (std::runtime_error("Could not lock SDL texture"));

	pixel_buffer = static_cast<Uint32*>(pixels);
	int thread_count = _pool.getSize();
	int rows_per_thread = h / thread_count;
	for (int t = 0; t < thread_count; ++t)
	{
		int start = t * rows_per_thread;
		int end = (t == thread_count - 1) ? h : (t + 1) * rows_per_thread;
		_pool.enqueue([&cam, &sc, start, end, w, pixel_buffer, &pitch, &skybox]()
		{
			Uint32 pixel_color;
			for (int y = start; y < end; ++y)
			{
				for (int x = 0; x < w; ++x)
				{
					Ray	ray = cam.pixelRay(x, y);
					HitRecord hit = sc.getBVH()->intersect(ray);
					if (hit.t >= 0 && hit.t < std::numeric_limits<float>::max())
						pixel_color = hit.mat->shade(ray, hit, sc);
					else
						pixel_color = skybox.shade(ray, hit, sc);
					pixel_buffer[y * (pitch / sizeof(Uint32)) + x] = pixel_color;
				}
			}
		});
	}
	_pool.wait();
	SDL_UnlockTexture(target.getTexture());
	SDL_RenderClear(renderer.getRenderer());
	SDL_RenderTexture(renderer.getRenderer(), target.getTexture(), NULL, NULL);
	SDL_RenderPresent(renderer.getRenderer());
}
