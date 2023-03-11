#pragma once

#include "direction.h"
#include <ostream>

class Velocity
{
public:
    Velocity() : dx(0.0), dy(0.0) {}
    Velocity(double dx, double dy) : dx(dx), dy(dy) {}
    Velocity(const Velocity & rhs) : dx(rhs.dx), dy(rhs.dy) {}
    Velocity(double speed, const Direction& direction) : dx(0.0), dy(0.0)
    {
        setSpeedDirection(speed, direction);
    }
    Velocity & operator = (const Velocity & rhs)
    {
        dx = rhs.dx;
        dy = rhs.dy;
        return *this;
    }

    double getDX()           const { return dx; }
    double getDY()           const { return dy; }
    double getSpeed()        const;
    Direction getDirection() const;

    void setDX(double dx)              { this->dx = dx;                }
    void setDY(double dy)              { this->dy = dy;                }
    void setDxDy(double dx, double dy) { this->dx = dx; this->dy = dy; }
    void setDirection(const Direction & direction)
    {
        setSpeedDirection(getSpeed(), direction);
    }
    void setSpeed(double speed)
    {
        setSpeedDirection(speed, getDirection());
    }
    void setSpeedDirection(double speed, const Direction & direction);

    void addDX(double dx) { setDX(getDX() + dx); }
    void addDY(double dy) { setDY(getDY() + dy); }
    void addV(const Velocity& v)
    {
        dx += v.dx;
        dy += v.dy;
    }
    Velocity& operator += (const Velocity& rhs)
    {
        addV(rhs);
        return *this;
    }
    void reverse()
    {
        dx *= -1.0;
        dy *= -1.0;
    }



private:
    double dx;
    double dy;
};

std::ostream& operator << (std::ostream& out, const Velocity& v);

class Acceleration
{
public:
    Acceleration() : ddx(0.0), ddy(0.0) {}
    Acceleration(double acc, const Direction& direction) : ddx(0.0), ddy(0.0)
    {
        setAccelerationDirection(acc, direction);
    }
    Velocity getVelocity(double time) const
    {
        return Velocity(ddx * time, ddy * time);
    }
    double getDDX() const { return ddx; }
    double getDDY() const { return ddy; }

    void setAccelerationDirection(double acc, const Direction& direction);



private:
    double ddx;
    double ddy;
};