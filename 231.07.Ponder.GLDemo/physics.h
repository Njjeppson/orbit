#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

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
	void simulate(double time_step, int numsteps, double& x, double& y, double& vx, double& vy, double m);
	double gravity(double h);
	double heightAboveEarth(double x, double y);
	double directionOfGravityPull(double xs, double ys);
	void acceleration(double m, double r, double theta, double& ax, double& ay);
};

#endif
