#include "../inc/BlinnPhongMaterial.hpp"

float			BlinnPhongMaterial::_shininess = 32.0f;
AmbientLight	BlinnPhongMaterial::_a = AmbientLight(1.0f, 1.0f, 1.0f, 0.2);

BlinnPhongMaterial::BlinnPhongMaterial(std::shared_ptr<ITexture> tex,
		float ref,
		std::optional<std::shared_ptr<ITexture>> normalMap)
	: _texture(tex), _reflectivity(ref), _normalMap(normalMap)
{
}

BlinnPhongMaterial::BlinnPhongMaterial(const BlinnPhongMaterial &other)
	: _texture(other._texture),
	_reflectivity(other._reflectivity),
	_normalMap(other._normalMap)
{
}

BlinnPhongMaterial&	BlinnPhongMaterial::operator=(const BlinnPhongMaterial &other)
{
	if (this == &other)
		return (*this);
	_texture = other._texture;
	_reflectivity = other._reflectivity;
	_normalMap = other._normalMap;
	return (*this);
}

Uint32	BlinnPhongMaterial::shade(const Ray &ray, const HitRecord &hit, const Scene &sc) const
{
	Vec3	base = _baseColor(ray, hit, sc);
	Vec3	refl;
	if (_reflectivity > 0)
		refl = _reflectionColor(ray, hit, sc);
	return(_mixColor(base, refl));
}

Vec3	BlinnPhongMaterial::_baseColor(
		const Ray &ray, const HitRecord &hit, const Scene &sc) const
{
	Vec3 tex_color = _texture->lookup(hit.u, hit.v, hit.point);
	Vec3 ambient = tex_color * _a.getColor() * _a.getIntensity();

	std::shared_ptr<ALight> l = sc.getLights()[0];
	Vec3 light_dir = (l->getPos() - hit.point).normalize();
	float light_distance = (l->getPos() - hit.point).length();
	Vec3 new_orig(hit.point + hit.normal * 1e-4);
	Ray shadow_ray(new_orig, light_dir);

	HitRecord shadow = sc.getBVH()->intersect(shadow_ray);
	if (shadow.t >= 0 && shadow.t < light_distance)
		return (ambient);

	Vec3 normal;
	if (_normalMap)
		normal = _sampleNormalMap(hit);
	else
		normal = hit.normal;

	float diff = fmax(dot(normal, light_dir), 0.0f);
	Vec3 diffuse = tex_color * l->getColor() * diff;

	Vec3 view_dir = (ray.dir * -1).normalize();
	Vec3 halfway = (light_dir + view_dir).normalize();
	float spec = powf(fmax(dot(normal, halfway), 0.0f), _shininess);
	Vec3 specular = l->getColor() * spec;

	Vec3 base = ambient + diffuse + specular;
	base.x = std::clamp(base.x, 0.0f, 1.0f);
	base.y = std::clamp(base.y, 0.0f, 1.0f);
	base.z = std::clamp(base.z, 0.0f, 1.0f);

	return (base);
}

Vec3	BlinnPhongMaterial::_reflectionColor(
		const Ray &ray, const HitRecord &hit, const Scene &sc) const
{
	Vec3 new_orig(hit.point + hit.normal * 1e-4);
	Ray refl_ray(new_orig, reflect(ray.dir, hit.normal));
	HitRecord r_hit = sc.getBVH()->intersect(refl_ray);
	if (r_hit.t >= 0 && r_hit.t < std::numeric_limits<float>::max())
		return (_baseColor(refl_ray, r_hit, sc));
	else
		return (Vec3());
}

Uint32	BlinnPhongMaterial::_mixColor(const Vec3 &base, const Vec3 &refl) const
{

	Uint8 red = static_cast<Uint8>(255 *
			(base.x * (1 - _reflectivity) + refl.x * _reflectivity));
	Uint8 green = static_cast<Uint8>(255 *
			(base.y * (1 - _reflectivity) + refl.y * _reflectivity));
	Uint8 blue = static_cast<Uint8>(255 *
			(base.z * (1 - _reflectivity) + refl.z * _reflectivity));
	return (red << 24 | green << 16 | blue << 8 | 0xFF);
}

Vec3	BlinnPhongMaterial::_sampleNormalMap(const HitRecord &hit) const
{
	Vec3 tangentNormal = _texture->lookup(hit.u, hit.v, hit.point);
	tangentNormal.x = tangentNormal.x * 2.0 - 1.0;
	tangentNormal.y = tangentNormal.y * 2.0 - 1.0;
	tangentNormal.z = tangentNormal.z * 2.0 - 1.0;
	Quaternion to_world(Vec3(0, 0, 1), hit.normal);
}
