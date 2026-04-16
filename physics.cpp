/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    Ethen Campbell
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/

#include "physics.h"  // for the prototypes

 /*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
    // Edge case: if no mappings are provided, return 0
    if (numMapping == 0) {
        return 0.0;
    }

    // Find the appropriate interval for interpolation
    int i = 0;
    while (i < numMapping && domain >= mapping[i].domain) {
        ++i;
    }

    // Handle edge cases where domain is outside the defined mappings
    if (i == 0) {
        return mapping[0].range;
    }
    else if (i == numMapping) {
        return mapping[numMapping - 1].range;
    }

    // Perform linear interpolation
    double d0 = mapping[i - 1].domain;
    double r0 = mapping[i - 1].range;
    double d1 = mapping[i].domain;
    double r1 = mapping[i].range;

    return r0 + (r1 - r0) * (domain - d0) / (d1 - d0);
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
    if (altitude <= 0.0)
        return 9.807; // sea level gravity

    if (altitude <= 10000.0)
    {
        // Linear interpolation between 0m and 10000m
        return 9.807 - (altitude / 10000.0) * (9.807 - 9.776);
    }
    else if (altitude <= 80000.0)
    {
        // Linear interpolation between 10000m and 80000m
        return 9.776 - ((altitude - 10000.0) / (80000.0 - 10000.0)) * (9.776 - 9.564);
    }
    else
    {
        // Above 80000m, gravity remains constant
        return 9.564;
    }
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
    const Mapping densityMapping[] =
    {
        // altitude, density
        {    0.0, 1.2250000},
        { 1000.0, 1.1120000},
        { 2000.0, 1.0070000},
        { 3000.0, 0.9093000},
        { 4000.0, 0.8194000},
        { 5000.0, 0.7364000},
        { 6000.0, 0.6601000},
        { 7000.0, 0.5900000},
        { 8000.0, 0.5258000},
        { 9000.0, 0.4671000},
        {10000.0, 0.4135000},
        {15000.0, 0.1948000},
        {20000.0, 0.0889100},
        {25000.0, 0.0400800},
        {30000.0, 0.0184100},
        {40000.0, 0.0039960},
        {50000.0, 0.0010270},
        {60000.0, 0.0003097},
        {70000.0, 0.0000828},
        {80000.0, 0.0000185}
    };

    // look up the value
    double density = linearInterpolation(densityMapping, sizeof(densityMapping) / sizeof(densityMapping[0]), altitude);

    return density;
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * Determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
    const Mapping speedMapping[] =
    {
        {0, 340},
        {1000, 336},
        {2000, 332},
        {3000, 328.51},
        {5000, 320},
        {6000, 316},
        {7000, 312},
        {8000, 308},
        {9000, 303},
        {10000, 299},
        {15000, 295},
        {20000, 295},
        {25000, 295},
        {30000, 305},
        {40000, 300},
        {50000, 209.7},
        {80000, 194}
    };

    double speed = linearInterpolation(speedMapping, sizeof(speedMapping) / sizeof(speedMapping[0]), altitude);

    return speed;
}

/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
    const Mapping dragSpeed[] =
    {
        // mach, drag
         {0.000,    0.0000},
         {0.300,	0.1629},
         {0.500,    0.1659},
         {0.700,	0.2031},
         {0.890,	0.2597},
         {0.920,	0.3010},
         {0.960,	0.3287},
         {0.980,	0.4002},
         {1.000,	0.4258},
         {1.020,	0.4335},
         {1.060,	0.4483},
         {1.240,	0.4064},
         {1.530,	0.3663},
         {1.990,	0.2897},
         {2.870,	0.2297},
         {2.890,	0.2306},
         {5.000,	0.2656}
    };

    // look up the value
    double drag = linearInterpolation(dragSpeed, sizeof(dragSpeed) / sizeof(dragSpeed[0]), speedMach);

    return drag;
}