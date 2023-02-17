using namespace std;
#include <cmath>

class Physics
{
private:
	double gh = 0;
	double h = 0;
	double d = 0;
	double ddx = 0;
	double ddy = 0;
	double dx = 0;
	double dy = 0;
	double s = 0;
	double v = 0;
	double t = 48;

public:

	double gravity(double h) {
		gh = 9.80665 * (6378000 / (6378000 + h));
		return gh;
	}

	double heightAboveEarth(double x, double y) {
		h = sqrt((x * x) + (y * y)) - 6378000;
		return h;
	}

	double directionOfGravityPull(double xs, double ys) {
		d = atan2(0 - xs, 0 - ys);
		return d;
	}

	double horizontalAcceleration(double a, double angle)
	{
		ddx = a * sin(angle);
		return ddx;
	}

	double verticalAcceleration(double a, double angle)
	{
		ddy = a * cos(angle);
		return ddy;
	}

	double newMotion (double s, double v) {
		s = s + v * t;
		return s;
	}

	double newHorizontalPosition(double x, double dx) {
		x = x + dx * t;
		return x;
	}

	double newVerticalPosition(double y, double dy) {
		y = y + dy * t;
		return y;
	}

	double newDistance(double s, double v, double a) {
		s = s + v * t + 0.5 * a * (t * t);
		return s;
	}

	double newVelocity(double v, double a) {
		v = v + a * t;
		return v;
	}

	double newHorizontalAndVerticalDistance(double x, double dx, double ddx) {
		x = x + dx * t + 0.5 * ddx * (t * t);
		return x;
	}

	double newHorizontalAndVerticalVelocity(double dx, double ddx) {
		dx = dx + ddx * t;
		return dx;
	}

	double calculateXPosition(double x, double y) {
		x = x + newHorizontalAndVerticalVelocity(dx, horizontalAcceleration(gravity(heightAboveEarth(x, y)), directionOfGravityPull(x, y))) * t;
		return x;
	}

	double calculateYPosition(double x, double y) {
		y = y + newHorizontalAndVerticalVelocity(dy, verticalAcceleration(gravity(heightAboveEarth(x, y)), directionOfGravityPull(x, y))) * t;
		return y;
	}
};