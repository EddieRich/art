#include <cmath>
#include "util.h"
#include "vec3.h"

vec3::vec3()
{
	val[0] = val[1] = val[2] = 0.0;
}

vec3::vec3(double v)
{
	val[0] = val[1] = val[2] = v;
}

vec3::vec3(double v0, double v1, double v2)
{
	val[0] = v0;
	val[1] = v1;
	val[2] = v2;
}

vec3 vec3::operator-() const { return vec3(-val[0], -val[1], -val[2]); }
double vec3::operator[](int i) const { return val[i]; }
double& vec3::operator[](int i) { return val[i]; }

vec3& vec3::operator+=(const vec3& v)
{
	val[0] += v[0];
	val[1] += v[1];
	val[2] += v[2];
	return *this;
}

vec3& vec3::operator*=(double t)
{
	val[0] *= t;
	val[1] *= t;
	val[2] *= t;
	return *this;
}

vec3& vec3::operator/=(double t)
{
	return *this *= 1 / t;
}

double vec3::length() const
{
	return std::sqrt(length_squared());
}

double vec3::length_squared() const
{
	return val[0] * val[0] + val[1] * val[1] + val[2] * val[2];
}

bool vec3::near_zero() const
{
	auto s = 1e-8;
	return (std::fabs(val[0]) < s) && (std::fabs(val[1]) < s) && (std::fabs(val[2]) < s);
}

vec3 vec3::random()
{
	return vec3(_R_(), _R_(), _R_());
}

vec3 vec3::random(double min, double max)
{
	return vec3(_R_(min, max), _R_(min, max), _R_(min, max));
}

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

// Vector Utility Functions
std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

vec3 operator*(double t, const vec3& v)
{
	return vec3(t * v[0], t * v[1], t * v[2]);
}

vec3 operator*(const vec3& v, double t)
{
	return t * v;
}

vec3 operator/(const vec3& v, double t)
{
	return (1 / t) * v;
}

double dot(const vec3& u, const vec3& v)
{
	return u[0] * v[0]
		+ u[1] * v[1]
		+ u[2] * v[2];
}

vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u[1] * v[2] - u[2] * v[1],
							u[2] * v[0] - u[0] * v[2],
							u[0] * v[1] - u[1] * v[0]);
}

vec3 unit_vector(const vec3& v)
{
	return v / v.length();
}

vec3 random_unit_vector()
{
	while (true)
	{
		auto p = vec3::random(-1, 1);
		auto lensq = p.length_squared();
		if (1e-160 < lensq && lensq <= 1)
			return p / sqrt(lensq);
	}
}

vec3 random_on_hemisphere(const vec3& normal)
{
	vec3 on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
		return on_unit_sphere;
	else
		return -on_unit_sphere;
}

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat)
{
	auto cos_theta = std::fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}
