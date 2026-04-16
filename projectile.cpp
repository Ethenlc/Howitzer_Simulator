#include "projectile.h"
#include "velocity.h"
#include "position.h"
#include "angle.h"
#include <cmath>

// Default constructor
Projectile::Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT), radius(DEFAULT_PROJECTILE_RADIUS)
{
}

// Reset method
void Projectile::reset()
{
    mass = DEFAULT_PROJECTILE_WEIGHT;
    radius = DEFAULT_PROJECTILE_RADIUS;
    flightPath.clear();
}

// Fire method
void Projectile::fire(const Angle& angle, const Position& pos, double muzzleVelocity)
{
    PositionVelocityTime pvt;
    pvt.pos = pos;
    pvt.t = 0.0; // Start time at 0.0

    // Use Angle class methods to get dx and dy components
    pvt.v = Velocity(muzzleVelocity * angle.getDx(), muzzleVelocity * angle.getDy());

    flightPath.push_back(pvt);
}

// Advance the projectile forward in time
void Projectile::advance(double simulationTime)
{
    const double gravity = 9.80665; // Acceleration due to gravity (m/s^2)
    const double dragCoefficient = 0.005; // Example drag coefficient

    if (!flightPath.empty())
    {
        PositionVelocityTime pvt = flightPath.back();

        // Calculate the drag force based on the velocity
        double velocityX = pvt.v.getDX();
        double velocityY = pvt.v.getDY();
        double speedSquared = velocityX * velocityX + velocityY * velocityY;

        // Calculate drag force components
        double dragForceX = -dragCoefficient * velocityX * fabs(velocityX) / mass;
        double dragForceY = -dragCoefficient * velocityY * fabs(velocityY) / mass;

        // Calculate acceleration
        double accelerationX = dragForceX;
        double accelerationY = -gravity + dragForceY;

        // Update the position
        double deltaX = velocityX * simulationTime + 0.5 * accelerationX * simulationTime * simulationTime;
        double deltaY = velocityY * simulationTime + 0.5 * accelerationY * simulationTime * simulationTime;

        pvt.pos.addMetersX(deltaX);
        pvt.pos.addMetersY(deltaY);

        // Update the velocity
        pvt.v.addDX(accelerationX * simulationTime);
        pvt.v.addDY(accelerationY * simulationTime);

        // Update time
        pvt.t += simulationTime;

        // Add the updated pvt to the flightPath
        flightPath.push_back(pvt);
    }
}
// Get the current position of the projectile
Position Projectile::getCurrentPosition() const
{
    if (!flightPath.empty())
    {
        return flightPath.back().pos;
    }
    return Position();
}


