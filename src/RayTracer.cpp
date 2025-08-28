#include "../inc/RayTracer.hpp"

RayTracer::RayTracer(const Camera &cam, const Scene &sc)
	: _cam(cam), _sc(sc), _max_depth(1)
{
}
