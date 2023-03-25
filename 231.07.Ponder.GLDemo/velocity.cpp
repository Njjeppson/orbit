#include "velocity.h"
#include "direction.h"

#define _USE_MATH_DEFINES
#include <cmath>

double Velocity :: getSpeed() const
{
    return sqrt(dx * dx + dy * dy);
}

Direction Velocity :: getDirection() const 
{
    Direction d;
    d.setDxDy(dx, dy);
    return d;
}

void Velocity :: setSpeedDirection(double speed, const Direction & direction)
{
    dy = speed * direction.getDy();
    dx = speed * direction.getDx();
}

void Acceleration :: setAccelerationDirection(double accel, const Direction& direction)
{
    ddy = accel * direction.getDy();
    ddx = accel * direction.getDx();
}

std::ostream& operator << (std::ostream& out, const Velocity& v)
{
    out << "[" << v.getDX() << "m/s, " << v.getDY() << "m/s]";
    return out;
}