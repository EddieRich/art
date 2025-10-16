#include <cmath>
#include <limits>
#include "interval.h"

interval::interval()
{
	min = std::numeric_limits<double>::max();
	max = std::numeric_limits<double>::min();
}

interval::interval(double min, double max)
{
	this->min = min;
	this->max = max;
}

double interval::size() const
{
	return max - min;
}

bool interval::contains(double x) const
{
	return min <= x && x <= max;
}

bool interval::surrounds(double x) const
{
	return min < x && x < max;
}

double interval::clamp(double x) const
{
	return std::fmax(min, std::fmin(x, max));
}
