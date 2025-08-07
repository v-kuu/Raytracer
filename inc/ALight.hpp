#pragma once
#include <stdexcept>

class	ALight
{
	public:
		ALight(void) = delete;
		ALight(float red, float green, float blue, float intensity);
		virtual	~ALight(void) = default;

		float	getRed(void) const;
		float	getGreen(void) const;
		float	getBlue(void) const;
		float	getIntensity(void) const;

	protected:
		float	_red;
		float	_green;
		float	_blue;
		float	_intensity;
};
