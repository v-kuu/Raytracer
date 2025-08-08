#include "../inc/Scene.hpp"
#include "../inc/PointLight.hpp"
#include "../inc/BlinnPhongMaterial.hpp"
#include "../inc/Sphere.hpp"

static HitRecord find_closest(std::vector<AHittable*> &objects, Ray &ray, int &i);
static Uint32	skybox(Ray ray);

Scene::Scene(void) : _cam(new Camera(90, Vec3(0, 0, 0), Vec3(0, 0, -1)))
{
	IMaterial *mat = new BlinnPhongMaterial(1.0f, 0.5f, 0.5f);
	_objects.push_back(new Sphere(2, Vec3(0, 0, -5), mat));
	_lights.push_back(new PointLight(1.0f, 1.0f, 1.0f, 1.0f, Vec3(-5, 10, -5)));
}

Scene::~Scene(void)
{
	delete _cam;
	for (AHittable* ptr : _objects)
		delete ptr;
	for (ALight* ptr : _lights)
		delete ptr;
}

Scene::Scene(const Scene &other)
	: _cam(other._cam), _objects(other._objects), _lights(other._lights)
{
}

Scene&	Scene::operator=(const Scene &other)
{
	if (this == &other)
		return (*this);
	_cam = other._cam;
	_objects = other._objects;
	_lights = other._lights;
	return (*this);
}

void	Scene::render(Texture *target)
{
	Renderer *renderer = target->getRenderer();
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
			int	obj_index = 0;
			HitRecord hit = find_closest(_objects, ray, obj_index);
			if (hit.t >= 0 && hit.t < std::numeric_limits<float>::max())
				pixel_color = _objects[0]->getMat()->shade(ray, hit, *this);
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

static HitRecord	find_closest(std::vector<AHittable*> &objects, Ray &ray, int &i)
{
	HitRecord closest = HitRecord(std::numeric_limits<float>::max(), Vec3(0, 0 ,0), Vec3(0, 0, 0));
	for (unsigned long j = 0; j < objects.size(); ++j)
	{
		HitRecord hit = objects[i]->detectHit(ray);
		if (hit.t < closest.t && hit.t >= 0)
		{
			closest = hit;
			i = static_cast<int>(j);
		}
	}
	return (closest);
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

const std::vector<AHittable*>& Scene::getObjects(void) const
{
	return (_objects);
}

const std::vector<ALight*>& Scene::getLights(void) const
{
	return (_lights);
}
