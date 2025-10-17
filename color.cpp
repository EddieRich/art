#include "interval.h"
#include "color.h"
#include <cmath>

inline double linear_to_gamma(double linear_component)
{
	if (linear_component > 0)
		return std::sqrt(linear_component);
	return 0;
}

std::ostream& operator<<(std::ostream& out, color& pixel_color)
{
	// Apply a linear to gamma transform for gamma 2
	auto r = linear_to_gamma(pixel_color[0]);
	auto g = linear_to_gamma(pixel_color[1]);
	auto b = linear_to_gamma(pixel_color[2]);

	// Translate the [0,1] component values to the byte range [0,255].
	static const interval intensity_clamp(0.000, 0.999);
	int rbyte = int(256 * intensity_clamp.clamp(pixel_color[0]));
	int gbyte = int(256 * intensity_clamp.clamp(pixel_color[1]));
	int bbyte = int(256 * intensity_clamp.clamp(pixel_color[2]));

	// Write out the pixel color components.
	return out << rbyte << ' ' << gbyte << ' ' << bbyte << ' ';
}
