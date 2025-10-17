#ifndef __CAMERA__
#define __CAMERA__

#include "observable.h"
#include "color.h"

class camera
{
public:
	double aspect_ratio = 1.0;	// Ratio of image width over height
	int image_width = 100;			// Rendered image width in pixel count
	int image_height = 0;				// initialize will handle this
	int alias_size = 0;					// anti-aliasing size
	int alias_mode = 0;					// 0=none, 1=rectangular, 2=random

	// part of material
	int max_depth = 10;					// maximum number of bounce rays
	color diffuse;							// diffuse color, should be defined in the observable

	void render(const observable& world);

private:
	point3 center;								// Camera center
	point3 viewport_upper_left;		// just what it says
	point3 pixel00_loc;						// Location of pixel 0, 0
	vec3   pixel_delta_u;					// Offset to pixel to the right
	vec3   pixel_delta_v;					// Offset to pixel below

	void initialize();
	color get_pixel_color(int x, int y, const observable& world) const;
	color ray_color(const ray& r, int depth, const observable& world) const;
};

#endif // __CAMERA__
