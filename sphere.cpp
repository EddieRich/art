#include <cmath>
#include "sphere.h"

sphere::sphere(const point3& center, double radius, std::shared_ptr<material> pmat)
{
	this->center = center;
	this->radius = std::fmax(0, radius);
	this->pmat = pmat;
}

bool sphere::hit(const ray& r, interval iv, hit_record& rec) const
{
	vec3 oc = center - r.origin();
	auto a = r.direction().length_squared();
	auto h = dot(r.direction(), oc);
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = h * h - a * c;
	if (discriminant < 0)
		return false;

	auto sqrtd = std::sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto root = (h - sqrtd) / a;
	if (!iv.surrounds(root))
	{
		root = (h + sqrtd) / a;
		if (!iv.surrounds(root))
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.pmat = pmat;

	return true;
}
