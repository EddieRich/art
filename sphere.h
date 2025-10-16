#ifndef __SPHERE__
#define __SPHERE__

#include "observable.h"
#include "vec3.h"

class sphere : public observable
{
public:
	sphere(const point3& center, double radius);

	bool hit(const ray& r, interval iv, hit_record& rec) const override;

private:
	point3 center;
	double radius;
};


#endif // __SPHERE__
