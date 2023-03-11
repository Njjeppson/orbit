#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <iostream>
class Direction
{
public:
	//constructors + assignment operator
	double degrees;
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
	float degreesFromRadians(double radians) const
	{
		/*
			r = angle in radians
			π = pi, about 3.14159
			d = angle in degrees
		*/
		// 	r / 2 π = d / 360
		double pi = M_PI;
		double degrees = radians * 180.0/pi;
		return degrees;
	}
	float radiansFromDegrees(double degrees) const
	{
		/*
			r = angle in radians
			π = pi, about 3.14159
			d = angle in degrees
		*/
		// 	r / 2 π = d / 360
		double pi = 2 * acos(0.0);
		double rhs = degrees * (2 * M_PI / 360.0);
		//cout << output << endl;
		setRadians(rhs);
	}

	// setters
	void setRadians(double rhs) const
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
		const_cast<float&>(radians) = rhs;
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
	double getDegrees() const { return degreesFromRadians(radians); }

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
	float radians;
};