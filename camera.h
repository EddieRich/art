#ifndef __CAMERA__
#define __CAMERA__

#include "observable.h"
#include "interval.h"
#include "color.h"

class camera
{
public:
	double aspect_ratio = 1.0;	// Ratio of image width over height
	int image_width = 100;			// Rendered image width in pixel count
	int image_height = 0;				// initialize will handle this
	int alias = 0;							// anti-aliasing size, 0 is none
	int alias_mode = 0;					// 0=rectangular, 1=random, 2=rectangular-random

	void render(const observable& world);

private:
	point3 center;         // Camera center
	point3 pixel00_loc;    // Location of pixel 0, 0
	vec3   pixel_delta_u;  // Offset to pixel to the right
	vec3   pixel_delta_v;  // Offset to pixel below

	void initialize();
	color ray_color(const ray& r, const observable& world) const;
};

#endif // __CAMERA__
