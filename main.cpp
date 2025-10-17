#include "camera.h"
#include "scene.h"
#include "sphere.h"
#include "material.h"

int main()
{
	scene world;

	//world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
	//world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

	auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto material_left = std::make_shared<dielectric>(1.50);
	auto material_bubble = std::make_shared<dielectric>(1.00 / 1.50);
	auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.2);
	world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
	world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
	world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	camera cam;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 800;
	cam.alias_mode = 1;
	cam.alias_size = 3;
	cam.max_depth = 50;
	cam.diffuse = color(0.5);

	cam.render(world);
}
