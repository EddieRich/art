#include "ray.h"

ray::ray()
{
	// really? do nothing?
}

ray::ray(const point3& origin, const vec3& direction)
{
	this->orig = origin;
	this->dir = direction;
}

const point3& ray::origin() const
{
	return orig;
}

const vec3& ray::direction() const
{
	return dir;
}

point3 ray::at(double t) const
{
	return orig + t * dir;
}
