#pragma once
#include <vector>
#include <limits>
#include <memory>
#include "Texture.hpp"
#include "Camera.hpp"
#include "ALight.hpp"
#include "IMaterial.hpp"
#include "AHittable.hpp"
#include "HitRecord.hpp"
#include "BVHNode.hpp"

class	AHittable;
class	ALight;
class	Camera;
struct	BVHNode;

class	Scene
{
	public:
		Scene(void);
		~Scene(void);
		Scene(const Scene &other);
		Scene	&operator=(const Scene &other);

		void	render(Texture *target);

		Camera							*getCam(void) const;
		const std::vector<AHittable*>	&getObjects(void) const;
		const std::vector<ALight*>		&getLights(void) const;

	private:
		Camera						*_cam;
		std::vector<AHittable*>		_objects;
		std::vector<ALight*>		_lights;
		std::shared_ptr<BVHNode>	_bvh;
};
