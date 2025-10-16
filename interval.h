#ifndef __INTERVAL__
#define __INTERVAL__

class interval
{
public:
	double min, max;

	interval();
	interval(double min, double max);

	double size() const;
	bool contains(double x) const;
	bool surrounds(double x) const;
	double clamp(double x) const;
};

#endif // __INTERVAL__
