using namespace std;
#include <cmath>

using namespace std;
#include <cmath>

class Physics
{
private:
	double x = 0;
	double y = 42164000.0;
	double gh;
	double h;
	double d;
	double ddx;
	double ddy;
	double dx;
	double dy;
	double s;
	double v;
	double a;
	double t = 48;

public:

	double gravity() {
		gh = 9.80665 * (6378000 / (6378000 + heightAboveEarth()));
		return gh;
	}

	double heightAboveEarth() {
		h = sqrt((x * x) + (y * y)) - 6378000;
		return h;
	}

	double directionOfGravityPull() {
		d = atan2(0 - x, 0 - y);
		return d;
	}

	double horizontalAcceleration()
	{
		ddx = gravity() * sin(directionOfGravityPull());
		return ddx;
	}

	double verticalAcceleration()
	{
		ddy = gravity() * cos(directionOfGravityPull());
		return ddy;
	}

	double newMotion() {
		s = s + v * t;
		return s;
	}

	double newHorizontalPosition() {
		x = x + dx * t;
		return x;
	}

	double newVerticalPosition() {
		y = y + dy * t;
		return y;
	}

	double newDistance() {
		s = s + v * t + 0.5 * a * (t * t);
		return s;
	}

	double newVelocity() {
		v = v + a * t;
		return v;
	}

	double newHorizontalDistance() {
		x = x + dx * t + 0.5 * ddx * (t * t);
		return x;
	}

	double newVerticalDistance() {
		y = y + dy * t + 0.5 * ddy * (t * t);
		return y;
	}

	double newHorizontalVelocity() {
		dx = dx + horizontalAcceleration() * t;
		return dx;
	}

	double newVerticalVelocity() {
		dy = dy + verticalAcceleration() * t;
		return dy;
	}

	double calculateXPosition() {
		x = x + newHorizontalVelocity() * t + 0.5 * ddx * (t * t);
		return x;
	}

	double calculateYPosition() {
		y = y + newVerticalVelocity() * t + 0.5 * ddy * (t * t);
		return y;
	}

	//double getX() {
		//return x;
	//}
};
