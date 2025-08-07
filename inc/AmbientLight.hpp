#pragma once
#include "ALight.hpp"

class	AmbientLight : public ALight
{
	public:
		AmbientLight(void) = delete;
		AmbientLight(float r, float g, float b, float intensity);
};
