#include "camera.h"
#include "util.h"
#include <limits>

void camera::render(const observable& world)
{
	initialize();

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int y = 0; y < image_height; y++)
	{
		std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
		for (int x = 0; x < image_width; x++)
		{
			color pixel_color = get_pixel_color(x, y, world);
			std::cout << pixel_color;
		}
		std::cout << '\n';
	}

	std::clog << "\rDone.                 \n";
}

void camera::initialize()
{
	if (image_height < 1)
		image_height = std::max(int(image_width / aspect_ratio), 1);

	center = point3(0, 0, 0);

	// Determine viewport dimensions.
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width) / image_height);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	pixel_delta_u = viewport_u / image_width;
	pixel_delta_v = viewport_v / image_height;

	// Calculate the location of the upper left pixel.
	viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

color camera::get_pixel_color(int x, int y, const observable& world) const
{
	// no anti-aliasing, just get the center pixel color
	if (alias_size < 1 || alias_mode < 1)
	{
		auto pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
		return ray_color(ray(center, pixel_center - center), max_depth, world);
	}
	// rectangular, no random
	else if (alias_mode == 1)
	{
		auto corner_pixel = viewport_upper_left + (x * pixel_delta_u) + (y * pixel_delta_v);
		auto subpixel_delta_u = pixel_delta_u / alias_size;
		auto subpixel_delta_v = pixel_delta_v / alias_size;
		color pixel_color;
		for (int j = 0; j <= alias_size; j++)
		{
			for (int i = 0; i <= alias_size; i++)
			{
				auto sub_pixel = corner_pixel + (i * subpixel_delta_u) + (j * subpixel_delta_v);
				pixel_color += ray_color(ray(center, sub_pixel - center), max_depth, world);
			}
		}

		pixel_color /= ((alias_size + 1) * (alias_size + 1));
		return pixel_color;
	}
	// random, full pixel
	else if (alias_mode == 2)
	{

		auto top_left = viewport_upper_left + (x * pixel_delta_u) + (y * pixel_delta_v);
		auto bottom_right = top_left + pixel_delta_u + pixel_delta_v;
		color pixel_color;
		for (int r = 0; r < alias_size; r++)
		{
			double a = _R_();
			auto sub_pixel = (1 - a) * top_left + a * bottom_right;
			pixel_color += ray_color(ray(center, sub_pixel - center), max_depth, world);
		}

		pixel_color /= alias_size;
		return pixel_color;
	}

	return color();
}

color camera::ray_color(const ray& r, int depth, const observable& world) const
{
	// If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth < 0)
		return color();

	hit_record rec;
	if (world.hit(r, interval(0.001, std::numeric_limits<double>::max()), rec))
	{
		// relflect in all directions (hemisphere)
		// vec3 direction = random_on_hemisphere(rec.normal);

		// True Lambertian Reflection
		vec3 direction = rec.normal + random_unit_vector();

		return diffuse * ray_color(ray(rec.p, direction), depth - 1, world);
		//return color(0.5 * (rec.normal + vec3(1, 1, 1)));
	}

	// hit the background
	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return color((1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0));
}
