#ifndef __SCENE__
#define __SCENE__

#include "observable.h"

#include <memory>
#include <vector>

class scene : public observable
{
public:
	std::vector<std::shared_ptr<observable>> objects;

	scene();
	scene(std::shared_ptr<observable> object);

	void clear();
	void add(std::shared_ptr<observable> object);

	bool hit(const ray& r, interval iv, hit_record& rec) const override;
};

#endif // __SCENE__
