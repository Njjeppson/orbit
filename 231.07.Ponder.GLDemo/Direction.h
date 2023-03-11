#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iostream>
class Direction
{
public:
	//constructors + assignment operator
	Direction() : radians(0.0) {}
	Direction(double degrees) : radians(0.0)
	{
		radians = radiansFromDegrees(degrees);
	}
	Direction(const Direction & rhs) : radians(rhs.radians) {}
	Direction& operator = (const Direction& rhs)
	{
		radians = rhs.radians;
		return *this;
	}

	// setters
	void setRadians(double rhs)
	{
		if (rhs >= 0.0)
		{
			double rotations = (double)(int)((M_PI + rhs) / (M_PI * 2.0));
			rhs -= rotations * (M_PI * 2.0);
		}
		else
		{
			double rotations = -(double)(int)((rhs - M_PI) / (M_PI * 2.0));
			rhs += rotations * (M_PI * 2.0);
		}
		radians = rhs;
	}

	void setDegrees(double rhs) { radians = radiansFromDegrees(rhs); }

	void setDxDy(double dx, double dy)
	{
		radians = atan2(dx, dy);
	}

	void setDown() { radians = M_PI; }
	void setUp() { radians = 0.0; }
	void setLeft() { radians = -M_PI_2; }
	void setRight() { radians = M_PI_2; }
	void reverse()
	{
		setRadians(radians + M_PI);
	}

	void rotate(double amount)
	{
		radians += amount;
		if (radians > M_PI)
			radians -= 2.0 * M_PI;
		if (radians < -M_PI)
			radians += 2.0 * M_PI;
	}

	// getters
	double getRadians() const { return radians; }
	double getDegrees() const { raturn degreesFromRadians(radians); }

	double getDx() const { return sin(radians); }
	double getDy() const { return cos(radians); }

	bool isRight() const { return radians > 0.0 && radians < M_PI; }
	bool isLeft() const { return radians < 0.0 && radians > -M_PI; }

	Direction operator+(double degrees) const
	{
		return Direction(getDegrees() + degrees);
	}
	Direction operator+(Direction rhs) const
	{
		rhs.rotate(radians);
		return rhs;
	}
private:

};