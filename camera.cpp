#include "camera.h"

void camera::render(const observable& world)
{
	initialize();

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int y = 0; y < image_height; y++)
	{
		std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
		for (int x = 0; x < image_width; x++)
		{
			auto pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);

			//ray r(center, pixel_center - center);
			color pixel_color = ray_color(ray(center, pixel_center - center), world);
			std::cout << pixel_color;
		}
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
	auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

color camera::ray_color(const ray& r, const observable& world) const
{
	hit_record rec;
	if (world.hit(r, interval(0, std::numeric_limits<double>::max()), rec))
	{
		return color(0.5 * (rec.normal + vec3(1, 1, 1)));
	}

	// hit the background
	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return color((1.0 - a) * vec3(1.0, 1.0, 1.0) + a * vec3(0.5, 0.7, 1.0));
}
