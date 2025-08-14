#include "../inc/Scene.hpp"
#include "../inc/PointLight.hpp"
#include "../inc/BlinnPhongMaterial.hpp"
#include "../inc/Sphere.hpp"

static Uint32	skybox(Ray ray);

Scene::Scene(void) : _cam(std::make_shared<Camera>(110, Vec3(0, 0, 0), Vec3(0, 0, -1)))
{
	std::shared_ptr<IMaterial> mat = std::make_shared<BlinnPhongMaterial>(1.0f, 0.5f, 0.5f);
	std::shared_ptr<IMaterial> mat2 = std::make_shared<BlinnPhongMaterial>(0.5f, 0.5f, 1.0f);
	_objects.push_back(std::make_unique<Sphere>(2, Vec3(2, 0, -10), mat));
	_objects.push_back(std::make_unique<Sphere>(2, Vec3(-3, 0, -5), mat2));
	_lights.push_back(std::make_shared<PointLight>(1.0f, 1.0f, 1.0f, 1.0f, Vec3(-5, 10, -5)));
	_bvh = std::make_unique<BVHNode>(_objects);
}

void	Scene::render(std::shared_ptr<Texture> target)
{
	std::shared_ptr<Renderer> renderer = target->getRenderer();
	void	*pixels;
	Uint32	*pixel_buffer;
	int		pitch;
	Uint32	pixel_color;
	int		w, h;

	if (!SDL_GetWindowSizeInPixels(Window::getInstance()->getWindow(), &w, &h))
	{
		throw (std::runtime_error("Failed to get texture size"));
	}
	if (!SDL_LockTexture(target->getTexture(), NULL, &pixels, &pitch))
		throw (std::runtime_error("Could not lock SDL texture"));
	pixel_buffer = static_cast<Uint32*>(pixels);
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			Ray	ray = _cam->pixelRay(x, y);
			HitRecord hit = _bvh->intersect(ray);
			if (hit.t >= 0 && hit.t < std::numeric_limits<float>::max())
				pixel_color = hit.mat->shade(ray, hit, *this);
			else
				pixel_color = skybox(ray);
			pixel_buffer[y * (pitch / sizeof(Uint32)) + x] = pixel_color;
		}
	}
	SDL_UnlockTexture(target->getTexture());
	SDL_RenderClear(renderer->getRenderer());
	SDL_RenderTexture(renderer->getRenderer(), target->getTexture(), NULL, NULL);
	SDL_RenderPresent(renderer->getRenderer());
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
