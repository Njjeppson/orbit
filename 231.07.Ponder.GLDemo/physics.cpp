using namespace std;
#include <cmath>

class Physics
{
private:
	double dx;
	double dy;
	double r;
	double a;
	double angle;
	double dt;
	double m;
public:

	void simulate(double time_step, int numsteps, double& x, double& y, double& vx, double& vy, double m) {
		// calculate initial distance and angle
		double r = sqrt(x * x + y * y);
		double theta = atan2(y, x);

		// calculate initial acceleration
		double ax, ay;
		acceleration(m, r, theta, ax, ay);

		// loop over time steps
		for (int i = 0; i < numsteps; i++) {
			// update velocity and position based on current acceleration and time step
			vx += ax * time_step;
			vy += ay * time_step;
			x += vx * time_step;
			y += vy * time_step;

			// calculate new distance and angle
			r = sqrt(x * x + y * y);
			theta = atan2(y, x);

			// calculate new acceleration based on updated position
			acceleration(m, r, theta, ax, ay);
		}
}

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

	void acceleration(double m, double r, double theta, double& ax, double& ay) {
		double G = 6.67e-11;
		double a = G * m / (r * r);
		ax = -a * sin(theta);
		ay = a * cos(theta);
	}
};
