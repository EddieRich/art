#ifndef __OBSERVABLE__
#define __OBSERVABLE__

#include "ray.h"
#include "interval.h"

class hit_record
{
public:
	point3 p;
	vec3 normal;
	double t;
	bool front_face;

	void set_face_normal(const ray& r, const vec3& outward_normal);
};

class observable
{
public:
	virtual ~observable() = default;

	virtual bool hit(const ray& r, interval iv, hit_record& rec) const = 0;
};


#endif // __OBSERVABLE__
