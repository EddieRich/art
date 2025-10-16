#ifndef __COLOR__
#define __COLOR__

#include <iostream>
#include "vec3.h"
#include "interval.h"

class color
{
public:

	color();
	color(double r, double g, double b);
	color(const vec3 v);

	double r() const { return rgb[0]; }
	double g() const { return rgb[1]; }
	double b() const { return rgb[2]; }


private:
	double rgb[3];
};

std::ostream& operator<<(std::ostream& out, color& color);

#endif // __COLOR__
