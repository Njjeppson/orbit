using namespace std;
#include <cmath>

class Physics
{
public:

	double gravity(double h) {
		double gh = 9.80665 * (6378000 / (6378000 + h));
		return gh;
	}

	double heightAboveEarth(double x, double y) {
		double h = sqrt((x * x) + (y * y)) - 6378000;
		return h;
	}

	double directionOfGravityPull(double xs, double ys) {
		double d = atan2(0 - xs, 0 - ys);
		return d;
	}

	double acceleration(double x, double y, double r, double a, double angle)
	{
		double ddx = a * sin(angle);
		double ddy = a * cos(angle);
		return sqrt((ddx * ddx) + (ddy * ddy));
	}

};