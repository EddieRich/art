#include "camera.h"
#include "scene.h"
#include "sphere.h"

int main()
{
	scene world;

	world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100));

	camera cam;
	cam.aspect_ratio = 16.0 / 9.0;
	cam.image_width = 800;
	cam.alias_mode = 1;
	cam.alias_size = 10;

	cam.render(world);
}
