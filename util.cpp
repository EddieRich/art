#include <random>
#include <numbers>
#include "util.h"

double deg2rad(double degrees)
{
	return degrees * std::numbers::pi * 180.0;
}

double _R_()
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

double _R_(double min, double max)
{
	return min + (max - min) * _R_();
}
