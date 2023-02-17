using namespace std;
#include <cmath>

class Physics
{
public:

	double heightAboveEarth(double x, double y, double r) {
		double h = sqrt((x * x) + (y * y)) - r;
		return h;
	}

};