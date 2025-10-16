#ifndef __RAY__
#define __RAY__

#include "vec3.h"

class ray
{
public:
	ray();
	ray(const point3& origin, const vec3& direction);

	const point3& origin() const;
	const vec3& direction() const;

	point3 at(double t) const;

private:
	point3 orig;
	vec3 dir;
};

#endif // __RAY__
