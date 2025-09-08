#include "../inc/Scene.hpp"

Scene::Scene(void) : _cam(std::make_shared<Camera>(90, Vec3(0, 0, 5), Vec3(0, 0, -1)))
{
	std::shared_ptr<ITexture> tex1 = std::make_shared<SolidColorTexture>(1.0f, 0.5f, 0.5f);
	std::shared_ptr<ITexture> tex2 = std::make_shared<SolidColorTexture>(0.5f, 0.5f, 1.0f);
	std::shared_ptr<ITexture> tex3 = std::make_shared<ImageTexture>("brick_floor_tileable_Base_Color.jpg");
	std::shared_ptr<IMaterial> mat = std::make_shared<BlinnPhongMaterial>(tex1, 0.5f);
	std::shared_ptr<IMaterial> mat2 = std::make_shared<BlinnPhongMaterial>(tex2, 0);
	std::shared_ptr<IMaterial> mat3 = std::make_shared<BlinnPhongMaterial>(tex3, 0);
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
