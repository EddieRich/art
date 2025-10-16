#include "color.h"

static const interval intensity_clamp(0.000, 0.999);

color::color()
{
	rgb[0] = rgb[1] = rgb[2] = 0.0;
}

color::color(double r, double g, double b)
{
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}

color::color(const vec3 v)
{
	rgb[0] = v[0];
	rgb[1] = v[1];
	rgb[2] = v[2];
}

color& color::operator+=(const color& c)
{
	rgb[0] += c.rgb[0];
	rgb[1] += c.rgb[1];
	rgb[2] += c.rgb[2];
	return *this;
}

color& color::operator*=(double t)
{
	rgb[0] *= t;
	rgb[1] *= t;
	rgb[2] *= t;
	return *this;
}

color& color::operator/=(double t)
{
	return *this *= 1 / t;
}

std::ostream& operator<<(std::ostream& out, color& color)
{
	// Translate the [0,1] component values to the byte range [0,255].
	int rbyte = int(256 * intensity_clamp.clamp(color.r()));
	int gbyte = int(256 * intensity_clamp.clamp(color.g()));
	int bbyte = int(256 * intensity_clamp.clamp(color.b()));

	// Write out the pixel color components.
	return out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ';
}
