#pragma once

#include <list>
#include "position.h"
#include "velocity.h"
#include "angle.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// Forward declaration for the unit test class
class TestProjectile;

/**********************************************************************
 * Projectile
 *    Everything we need to know about a projectile
 ************************************************************************/
class Projectile
{
public:
    // Friend the unit test class
    friend class TestProjectile;

    // Default constructor
    Projectile();

    // Reset method
    void reset();

    // Fire method
    void fire(const Angle& angle, const Position& pos, double muzzleVelocity);

    // Advance the projectile forward in time
    void advance(double simulationTime);

    // Get the current position of the projectile
    Position getCurrentPosition() const;

    // Keep track of one moment in the path of the projectile
    struct PositionVelocityTime
    {
        PositionVelocityTime() : pos(), v(), t(0.0) {}
        Position pos;
        Velocity v;
        double t;
    };

    double mass;           // Weight of the projectile. Defaults to DEFAULT_PROJECTILE_WEIGHT
    double radius;         // Radius of the projectile. Defaults to DEFAULT_PROJECTILE_RADIUS
    std::list<PositionVelocityTime> flightPath;

private:
    // Private helper function for calculating new position and velocity
    void calculateNewPositionVelocity(PositionVelocityTime& pvt, double deltaTime);
};
