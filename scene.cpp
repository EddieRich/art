#include "scene.h"

scene::scene()
{}

scene::scene(std::shared_ptr<observable> object)
{
	add(object);
}

void scene::clear()
{
	objects.clear();
}

void scene::add(std::shared_ptr<observable> object)
{
	objects.push_back(object);
}

bool scene::hit(const ray& r, interval iv, hit_record& rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest_so_far = iv.max;

	for (const auto& object : objects)
	{
		if (object->hit(r, interval(iv.min, closest_so_far), temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}
