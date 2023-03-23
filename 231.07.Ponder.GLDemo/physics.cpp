#include "physics.h"
#include "position.h"
#include "direction.h"
#include "velocity.h"

const double earthRadius = 6378000.0;

double getAltitude(const Position& posElement)
{
    double distance = computeDistance(Position(), posElement);
    return distance - earthRadius;
}

Acceleration getGravity(const Position& posElement)
{
    double height = getAltitude(posElement);

    Direction direction;
    direction.setDxDy(-posElement.getMetersX(), -posElement.getMetersY());

    double standardGravity = 9.806;
    double tmp = earthRadius / (earthRadius + height);
    double acceleration = standardGravity * tmp * tmp;

    return Acceleration(acceleration, direction);
}

Velocity& updateVelocity(Velocity& velocity, const Acceleration& acceleration, double time)
{
    velocity.addDX(acceleration.getDDX() * time);
    velocity.addDY(acceleration.getDDY() * time);
    return velocity;
}

Position& updatePosition(Position& pos, const Velocity& vel, const Acceleration& acc, double time)
{
    pos.addMetersX(vel.getDX() * time + 0.5 * acc.getDDX() * time * time);
    pos.addMetersY(vel.getDY() * time + 0.5 * acc.getDDY() * time * time);
    return pos;
}