#ifndef __VEC3__
#define __VEC3__

#include <iostream>

class vec3
{
public:
	vec3();
	vec3(double v);
	vec3(double v0, double v1, double v2);

	double x() const { return val[0]; }
	double y() const { return val[1]; }
	double z() const { return val[2]; }

	vec3 operator-() const;
	double operator[](int i) const;
	double& operator[](int i);
	vec3& operator+=(const vec3& v);
	vec3& operator*=(double t);
	vec3& operator/=(double t);
	double length() const;
	double length_squared() const;
	bool near_zero() const;

	static vec3 random();
	static vec3 random(double min, double max);

private:
	double val[3];
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// Vector Utility Functions
std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(double t, const vec3& v);
vec3 operator*(const vec3& v, double t);
vec3 operator/(const vec3& v, double t);
double dot(const vec3& u, const vec3& v);
vec3 cross(const vec3& u, const vec3& v);
vec3 unit_vector(const vec3& v);
vec3 random_unit_vector();
vec3 random_on_hemisphere(const vec3& normal);
vec3 reflect(const vec3& v, const vec3& n);
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat);

#endif // __VEC3__
