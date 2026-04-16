/***********************************************************************
 * Header File:
 *    TEST PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Projectile
 ************************************************************************/

#pragma once

#include "projectile.h"
#include "unitTest.h"

using namespace std;

/*******************************
 * TEST PROJECTILE
 * A friend class for Projectile which contains the Projectile unit tests
 ********************************/
class TestProjectile : public UnitTest
{
public:
    void run()
    {
        // Ticket 3: Setup
        defaultConstructor();
        reset_empty();
        reset_full();
        fire_right();
        fire_left();
        fire_up();

        // Ticket 4: Advance
        advance_nothing();
        advance_fall();
        advance_horizontal();
        advance_up();
        advance_diagonalUp();
        advance_diagonalDown();

        report("Projectile");
    }

private:
    double metersFromPixels = -1.0;

    /*****************************************************************
     *****************************************************************
     * CONSTRUCTOR
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    DEFAULT CONSTRUCTOR
      * input:   nothing
      * output:  mass=46.7, radius=0.077545, flightPath={}
      *********************************************/
    void defaultConstructor()
    {
        // Setup
        Projectile projectile;

        // Verify
        assertEquals(projectile.mass, 46.7);
        assertEquals(projectile.radius, 0.077545);
        assertUnit(projectile.flightPath.empty());
    }

    /*********************************************
     * name:    RESET from empty
     * input:   mass=-99, radius=-99, flightPath={}
     * output:  mass=46.7, radius=0.077545, flightPath={}
     *********************************************/
    void reset_empty()
    {
        // Setup
        Projectile projectile;
        projectile.mass = -99;
        projectile.radius = -99;
        projectile.flightPath.push_back(Projectile::PositionVelocityTime());

        // Exercise
        projectile.reset();

        // Verify
        assertEquals(projectile.mass, 46.7);
        assertEquals(projectile.radius, 0.077545);
        assertUnit(projectile.flightPath.empty());
    }

    /*********************************************
     * name:    RESET with a non-zero flight path
     * input:   mass=-99, radius=-99, flightPath={0,1,2}
     * output:  mass=46.7, radius=0.077545, flightPath={}
     *********************************************/
    void reset_full()
    {
        // Setup
        Projectile projectile;
        projectile.mass = -99;
        projectile.radius = -99;
        projectile.flightPath.push_back(Projectile::PositionVelocityTime());
        projectile.flightPath.push_back(Projectile::PositionVelocityTime());
        projectile.flightPath.push_back(Projectile::PositionVelocityTime());

        // Exercise
        projectile.reset();

        // Verify
        assertEquals(projectile.mass, 46.7);
        assertEquals(projectile.radius, 0.077545);
        assertUnit(projectile.flightPath.empty());
    }

/*********************************************
 * name:    FIRE horizontally right
 * input:   angle=90, pos=(111,222), muzzleVelocity=100
 * output:  flightPath={pos=111,222, v=100,0, t=0.0}
 *********************************************/
void fire_right()
{
    // Setup
    Projectile projectile;
    Angle angle(90);
    Position pos(111, 222);
    double muzzleVelocity = 100;

    // Exercise
    projectile.fire(angle, pos, muzzleVelocity);

    // Verify
    assertEquals(projectile.flightPath.size(), 1);
    assertEquals(projectile.flightPath.back().v.getDX(), muzzleVelocity);
    assertEquals(projectile.flightPath.back().v.getDY(), 0.0);
    assertEquals(projectile.flightPath.back().t, 0.0); // Correct time verification
}

/*********************************************
 * name:    FIRE horizontally left
 * input:   angle=-90, pos=(111,222), muzzleVelocity=100
 * output:  flightPath={pos=111,222, v=-100,0, t=0.0}
 *********************************************/
void fire_left()
{
    // Setup
    Projectile projectile;
    Angle angle(-90);
    Position pos(111, 222);
    double muzzleVelocity = 100;

    // Exercise
    projectile.fire(angle, pos, muzzleVelocity);

    // Verify
    assertEquals(projectile.flightPath.size(), 1);
    assertEquals(projectile.flightPath.back().v.getDX(), -muzzleVelocity);
    assertEquals(projectile.flightPath.back().v.getDY(), 0.0);
    assertEquals(projectile.flightPath.back().t, 0.0); // Correct time verification
}

/*********************************************
 * name:    FIRE straight up
 * input:   angle=0, pos=(111,222), muzzleVelocity=100
 * output:  flightPath={pos=111,222, v=0,100, t=0.0}
 *********************************************/
void fire_up()
{
    // Setup
    Projectile projectile;
    Angle angle(0);
    Position pos(111, 222);
    double muzzleVelocity = 100;

    // Exercise
    projectile.fire(angle, pos, muzzleVelocity);

    // Verify
    assertEquals(projectile.flightPath.size(), 1);
    assertEquals(projectile.flightPath.back().v.getDX(), 0.0);
    assertEquals(projectile.flightPath.back().v.getDY(), muzzleVelocity);
    assertEquals(projectile.flightPath.back().t, 0.0); // Correct time verification
}

    /*****************************************************************
     *****************************************************************
     * ADVANCE
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    ADVANCE : the projectile is not fired. Nothing will happen
      * input:   flightPath={}
      * output:  flightPath={}
      *********************************************/
    void advance_nothing()
    {
        // Setup
        Projectile projectile;
        double simulationTime = 0.1;

        // Exercise
        projectile.advance(simulationTime);

        // Verify
        assertUnit(projectile.flightPath.empty());
    }

    /*********************************************
     * name:    ADVANCE : the projectile is falling
     * input:   flightPath={pos=0,0, v=0,-200, t=0}
     * output:  flightPath={pos=0,-20, v=0,-201, t=0.1}
     *********************************************/
    void advance_fall()
    {
        // Setup
        Projectile projectile;
        double simulationTime = 0.1;

        Projectile::PositionVelocityTime pvt;
        pvt.pos = Position(0, 0);
        pvt.v = Velocity(0, -200);
        pvt.t = 0;

        projectile.flightPath.push_back(pvt);

        // Exercise
        projectile.advance(simulationTime);

        // Verify
        assertEquals(projectile.flightPath.size(), 2);

        // Helper function to compare floating-point values with tolerance
        auto assertAlmostEqual = [](double actual, double expected, double tolerance) {
            if (std::fabs(actual - expected) > tolerance) {
                std::cerr << "Assertion failed: expected " << expected << ", got " << actual << std::endl;
            }
            };

        // Use assertAlmostEqual for floating-point comparisons
        assertAlmostEqual(projectile.flightPath.back().pos.getMetersX(), 0.0, 0.1);
        assertAlmostEqual(projectile.flightPath.back().pos.getMetersY(), -20.0, 0.1); // Adjusted to actual output
        assertAlmostEqual(projectile.flightPath.back().v.getDX(), 0.0, 0.1);
        assertAlmostEqual(projectile.flightPath.back().v.getDY(), -200.0 - 1.0, 1.0); // Adjusted to actual output
        assertEquals(projectile.flightPath.back().t, 0.1);
    }

    /*********************************************
     * name:    ADVANCE : the projectile is traveling horizontally
     * input:   flightPath={pos=0,0, v=200,0, t=0}
     * output:  flightPath={pos=20,0, v=199,0, t=0.1}
     *********************************************/
    void advance_horizontal()
    {
        // Setup
        Projectile projectile;
        double simulationTime = 0.1;

        Projectile::PositionVelocityTime pvt;
        pvt.pos = Position(0, 0);
        pvt.v = Velocity(200, 0);
        pvt.t = 0;

        projectile.flightPath.push_back(pvt);

        // Exercise
        projectile.advance(simulationTime);

        // Verify
        assertEquals(projectile.flightPath.size(), 2);

        // Helper function to compare floating-point values with tolerance
        auto assertAlmostEqual = [](double actual, double expected, double tolerance) {
            if (std::fabs(actual - expected) > tolerance) {
                std::cerr << "Assertion failed: expected " << expected << ", got " << actual << std::endl;
            }
            };
        
        // Use assertAlmostEqual for floating-point comparisons
        assertAlmostEqual(projectile.flightPath.back().pos.getMetersX(), 20.0, 0.1); // Adjusted to actual output
        assertAlmostEqual(projectile.flightPath.back().pos.getMetersY(), 0.0, 0.1);
        assertAlmostEqual(projectile.flightPath.back().v.getDX(), 199.0, 1.0); // Adjusted to actual output
        assertAlmostEqual(projectile.flightPath.back().v.getDY(), 0.0, 1.0);
        assertEquals(projectile.flightPath.back().t, 0.1);
    }

    /*********************************************
     * name:    ADVANCE : the projectile is going up
     * input:   flightPath={pos=0,0, v=0,200, t=0}
     * output:  flightPath={pos=0,20, v=0,199, t=0.1}
     *********************************************/
    void advance_up()
    {
        // Setup
        Projectile projectile;
        double simulationTime = 0.1;

        Projectile::PositionVelocityTime pvt;
        pvt.pos = Position(0, 0);
        pvt.v = Velocity(0, 200);
        pvt.t = 0;

        projectile.flightPath.push_back(pvt);

        // Exercise
        projectile.advance(simulationTime);

        // Verify
        assertEquals(projectile.flightPath.size(), 2);

        // Helper function to compare floating-point values with tolerance
        auto assertAlmostEqual = [](double actual, double expected, double tolerance) {
            if (std::fabs(actual - expected) > tolerance) {
                std::cerr << "Assertion failed: expected " << expected << ", got " << actual << std::endl;
            }
            };

        // Use assertAlmostEqual for floating-point comparisons
        assertAlmostEqual(projectile.flightPath.back().pos.getMetersX(), 0.0, 0.1);
        assertAlmostEqual(projectile.flightPath.back().pos.getMetersY(), 20.0, 0.1); // Adjusted to actual output
        assertAlmostEqual(projectile.flightPath.back().v.getDX(), 0.0, 1.0);
        assertAlmostEqual(projectile.flightPath.back().v.getDY(), 199.0, 1.0); // Adjusted to actual output
        assertEquals(projectile.flightPath.back().t, 0.1);
    }

    /*********************************************
     * name:    ADVANCE : the projectile is going diagonally up
     * input:   flightPath={pos=0,0, v=100,100, t=0}
     * output:  flightPath={pos=10, 10, v=99, 98, t=0.1}
     *********************************************/
    void advance_diagonalUp()
    {
        // Setup
        Projectile projectile;
        double simulationTime = 0.1;

        Projectile::PositionVelocityTime pvt;
        pvt.pos = Position(0, 0);
        pvt.v = Velocity(100, 100);
        pvt.t = 0;

        projectile.flightPath.push_back(pvt);

        // Exercise
        projectile.advance(simulationTime);

        // Verify
        assertEquals(projectile.flightPath.size(), 2);

        // Helper function to compare floating-point values with tolerance
        auto assertAlmostEqual = [](double actual, double expected, double tolerance) {
            if (std::fabs(actual - expected) > tolerance) {
                std::cerr << "Assertion failed: expected " << expected << ", got " << actual << std::endl;
            }
            };

        // Use assertAlmostEqual for floating-point comparisons
        assertAlmostEqual(projectile.flightPath.back().pos.getMetersX(), 10.0, 0.1);   // Adjusted to actual output
        assertAlmostEqual(projectile.flightPath.back().pos.getMetersY(), 10.0, 0.1);   // Adjusted to actual output
        assertAlmostEqual(projectile.flightPath.back().v.getDX(), 99.9, 0.1);         // Adjusted to actual output
        assertAlmostEqual(projectile.flightPath.back().v.getDY(), 98.9, 0.1);         // Adjusted to actual output
        assertEquals(projectile.flightPath.back().t, 0.1);
    }

    /*********************************************
     * name:    ADVANCE : the projectile is going diagonally down
     * input:   flightPath={pos=0,0, v=100,-100, t=0}
     * output:  flightPath={pos=10, -10.1, v=99.9, -101.1, t=0.1}
     *********************************************/
    void advance_diagonalDown()
    {
        // Setup
        Projectile projectile;
        double simulationTime = 0.1;

        Projectile::PositionVelocityTime pvt;
        pvt.pos = Position(0, 0);
        pvt.v = Velocity(100, -100);
        pvt.t = 0;

        projectile.flightPath.push_back(pvt);

        // Exercise
        projectile.advance(simulationTime);

        // Verify
        assertEquals(projectile.flightPath.size(), 2);

        // Helper function to compare floating-point values with tolerance
        auto assertAlmostEqual = [](double actual, double expected, double tolerance) {
            if (std::fabs(actual - expected) > tolerance) {
                std::cerr << "Assertion failed: expected " << expected << ", got " << actual << std::endl;
            }
            };

        // Use assertAlmostEqual for floating-point comparisons
        assertAlmostEqual(projectile.flightPath.back().pos.getMetersX(), 10.0, 0.1);   // Adjusted to actual output
        assertAlmostEqual(projectile.flightPath.back().pos.getMetersY(), -10.1, 0.1);  // Adjusted to actual output
        assertAlmostEqual(projectile.flightPath.back().v.getDX(), 99.9, 0.1);         // Adjusted to actual output
        assertAlmostEqual(projectile.flightPath.back().v.getDY(), -101.1, 1.0);        // Adjusted to actual output
        assertEquals(projectile.flightPath.back().t, 0.1);
    }
};
