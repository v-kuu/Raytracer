#pragma once
#include <vector>
#include <limits>
#include "Texture.hpp"
#include "Camera.hpp"
#include "ALight.hpp"
#include "IMaterial.hpp"
#include "AHittable.hpp"
#include "HitRecord.hpp"

class	AHittable;
class	ALight;
class	Camera;

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
		Camera					*_cam;
		std::vector<AHittable*>	_objects;
		std::vector<ALight*>	_lights;
};
