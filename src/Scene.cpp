#include "../inc/Scene.hpp"

Scene::Scene(void) : _cam(std::make_shared<Camera>(90, Vec3(0, 0, 5), Vec3(0, 0, -1)))
{
	std::shared_ptr<IMaterial> mat = std::make_shared<BlinnPhongMaterial>(1.0f, 0.5f, 0.5f, 0.2f);
	std::shared_ptr<IMaterial> mat2 = std::make_shared<BlinnPhongMaterial>(0.5f, 0.5f, 1.0f, 0);
	std::shared_ptr<IMaterial> mat3 = std::make_shared<NormalMaterial>();
	_objects.push_back(std::make_unique<Sphere>(2, Vec3(2, 0, -10), mat));
	_objects.push_back(std::make_unique<Sphere>(2, Vec3(-3, 0, -5), mat2));
	_objects.push_back(std::make_unique<Sphere>(3, Vec3(0, 0, -15), mat3));
	_objects.push_back(std::make_unique<Triangle>(
				Vec3(0, -4, 5),
				Vec3(-20, -4, -20),
				Vec3(20, -4, -20),
				mat));
	_lights.push_back(std::make_shared<PointLight>(1.0f, 1.0f, 1.0f, 1.0f, Vec3(-5, 10, -5)));
	_bvh = std::make_unique<BVHNode>(_objects);
}

void	Scene::render(std::shared_ptr<Texture> target, ThreadPool &pool)
{
	std::shared_ptr<Renderer> renderer = target->getRenderer();
	SkyboxMaterial	skybox;
	void	*pixels;
	Uint32	*pixel_buffer;
	int		pitch, w, h;

	if (!SDL_GetWindowSizeInPixels(Window::getInstance()->getWindow(), &w, &h))
		throw (std::runtime_error("Failed to get texture size"));
	if (!SDL_LockTexture(target->getTexture(), NULL, &pixels, &pitch))
		throw (std::runtime_error("Could not lock SDL texture"));
	pixel_buffer = static_cast<Uint32*>(pixels);
	int thread_count = pool.getSize();
	int rows_per_thread = h / thread_count;
	for (int t = 0; t < thread_count; ++t)
	{
		int start = t * rows_per_thread;
		int end = (t == thread_count - 1) ? h : (t + 1) * rows_per_thread;
		pool.enqueue([this, start, end, w, pixel_buffer, pitch, skybox]()
		{
			Uint32 pixel_color;
			for (int y = start; y < end; ++y)
			{
				for (int x = 0; x < w; ++x)
				{
					Ray	ray = _cam->pixelRay(x, y);
					HitRecord hit = _bvh->intersect(ray);
					if (hit.t >= 0 && hit.t < std::numeric_limits<float>::max())
						pixel_color = hit.mat->shade(ray, hit, *this);
					else
						pixel_color = skybox.shade(ray, hit, *this);
					pixel_buffer[y * (pitch / sizeof(Uint32)) + x] = pixel_color;
				}
			}
		});
	}
	pool.wait();
	SDL_UnlockTexture(target->getTexture());
	SDL_RenderClear(renderer->getRenderer());
	SDL_RenderTexture(renderer->getRenderer(), target->getTexture(), NULL, NULL);
	SDL_RenderPresent(renderer->getRenderer());
}

std::shared_ptr<Camera>	Scene::getCam(void) const
{
	return (_cam);
}

const std::vector<std::unique_ptr<AHittable>>& Scene::getObjects(void) const
{
	return (_objects);
}

const std::vector<std::shared_ptr<ALight>>& Scene::getLights(void) const
{
	return (_lights);
}

const std::unique_ptr<BVHNode>&	Scene::getBVH(void) const
{
	return (_bvh);
}
