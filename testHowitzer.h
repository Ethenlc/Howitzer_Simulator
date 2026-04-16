/***********************************************************************
 * Header File:
 *    TEST HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    All the unit tests for Howitzer
 ************************************************************************/

#pragma once

#include "howitzer.h"
#include "position.h"
#include "unitTest.h"

 /*******************************
  * TEST HOWITZER
  * A friend class for Howitzer which contains the Howitzer unit tests
  ********************************/
class TestHowitzer : public UnitTest
{
public:
    void run()
    {
        // Ticket 1: Getters
        defaultConstructor();
        getPosition_zero();
        getPosition_middle();
        getMuzzleVelocity_slow();
        getMuzzleVelocity_standard();
        getElevation_up();
        getElevation_right();
        getElevation_left();

        // Ticket 2: Setters
        generatePosition_small();
        generatePosition_large();
        raise_rightDown();
        raise_rightUp();
        raise_leftDown();
        raise_leftUp();
        rotate_clock();
        rotate_counterClock();
        rotate_wrapClock();
        rotate_wrapCounterClock();

        report("Howitzer");
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
      * output:  zeros (except angle is at 45 degrees,
      *                 and the muzzle velocity is correct)
      *********************************************/
    void defaultConstructor()
    {
        // Setup
        Howitzer howitzer;

        // Verify
        assertEquals(howitzer.position.getPixelsX(), 0.0);
        assertEquals(howitzer.position.getPixelsY(), 0.0);
        assertEquals(howitzer.muzzleVelocity, DEFAULT_MUZZLE_VELOCITY);
        assertEquals(howitzer.elevation.getDegrees(), 45.0);
    }

    /*****************************************************************
     *****************************************************************
     * GETTERS
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    GET POSITION ZERO
      * input:   h.pos=(0,0)
      * output:  pos=(0,0)
      *********************************************/
    void getPosition_zero()
    {
        // Setup
        Howitzer howitzer;
        howitzer.position.setPixelsX(0.0);
        howitzer.position.setPixelsY(0.0);

        // Verify
        assertEquals(howitzer.getPosition().getPixelsX(), 0.0);
        assertEquals(howitzer.getPosition().getPixelsY(), 0.0);
    }

    /*********************************************
     * name:    GET POSITION MIDDLE
     * input:   h.pos=(123.4, 567.8)
     * output:  pos=(123.4, 567.8)
     *********************************************/
    void getPosition_middle()
    {
        // Setup
        Howitzer howitzer;
        howitzer.position.setPixelsX(123.4);
        howitzer.position.setPixelsY(567.8);

        // Verify
        assertEquals(howitzer.getPosition().getPixelsX(), 123.4);
        assertEquals(howitzer.getPosition().getPixelsY(), 567.8);
    }

    /*********************************************
     * name:    GET MUZZLE VELOCITY - SLOW SPEED
     * input:   h.muzzleVelocity=(24.68)
     * output:  m=24.68
     *********************************************/
    void getMuzzleVelocity_slow()
    {
        // Setup
        Howitzer howitzer;
        howitzer.muzzleVelocity = 24.68;

        // Verify
        assertEquals(howitzer.getMuzzleVelocity(), 24.68);
    }

    /*********************************************
     * name:    GET MUZZLE VELOCITY - STANDARD SPEED
     * input:   h.muzzleVelocity=(827.00)
     * output:  m=827
     *********************************************/
    void getMuzzleVelocity_standard()
    {
        // Setup
        Howitzer howitzer;

        // Verify
        assertEquals(howitzer.getMuzzleVelocity(), DEFAULT_MUZZLE_VELOCITY);
    }

    /*********************************************
     * name:    GET ELEVATION - up
     * input:   h.elevation=0
     * output:  e=0
     *********************************************/
    void getElevation_up()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setDegrees(0.0);

        // Verify
        assertEquals(howitzer.getElevation().getDegrees(), 0.0);
    }

    /*********************************************
     * name:    GET ELEVATION - right
     * input:   h.elevation=0.4
     * output:  e=0.4
     *********************************************/
    void getElevation_right()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setRadians(0.4);

        // Verify
        assertEquals(howitzer.getElevation().getRadians(), 0.4);
    }

    /*********************************************
     * name:    GET ELEVATION - left
     * input:   h.elevation=5.8
     * output:  e=5.8
     *********************************************/
    void getElevation_left()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setRadians(5.8);

        // Verify
        assertEquals(howitzer.getElevation().getRadians(), 5.8);
    }

    /*****************************************************************
     *****************************************************************
     * SETTERS
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    GENERATE POSITION small board
      * input:   (10px, 10px)
      * output:  1px <= x <= 9px
      *********************************************/
    void generatePosition_small()
    {
        // Setup
        Howitzer howitzer;
        Position posUpperRight;
        posUpperRight.setPixelsX(10);
        posUpperRight.setPixelsY(10);

        // Exercise
        howitzer.generatePosition(posUpperRight);

        // Verify
        double posX = howitzer.getPosition().getPixelsX();
        if (!(posX >= 1.0 && posX <= 9.0))
        {
            std::cerr << "Assertion failed: Position X is out of expected range. Got: " << posX << std::endl;
            std::exit(EXIT_FAILURE);
        }
        assertEquals(howitzer.getPosition().getPixelsY(), 0.0, "Position Y is not 0");
    }

    /*********************************************
    * name:    GENERATE POSITION large board
    * input:   (1000px, 1000px)
    * output:  100px <= x <= 900px
    *********************************************/
    void generatePosition_large()
    {
        // Setup
        Howitzer howitzer;
        Position posUpperRight;
        posUpperRight.setPixelsX(1000);
        posUpperRight.setPixelsY(1000);

        // Exercise
        howitzer.generatePosition(posUpperRight);

        // Verify
        double posX = howitzer.getPosition().getPixelsX();
        if (!(posX >= 100.0 && posX <= 900.0))
        {
            std::cerr << "Assertion failed: Position X is out of expected range. Got: " << posX << std::endl;
            std::exit(EXIT_FAILURE);
        }
        assertEquals(howitzer.getPosition().getPixelsY(), 0.0, "Position Y is not 0");
    }

    /*********************************************
    * name:    RAISE to the right/down
    * input:   h.elevation=0.5radians  raise(-0.1)
    * output:  h.elevation=0.6radians
    *********************************************/
    void raise_rightDown()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setRadians(0.5);

        // Exercise
        howitzer.raise(-0.1);

        // Verify
        assertEquals(howitzer.getElevation().getRadians(), 0.6);
    }

    /*********************************************
    * name:    RAISE to the right/up
    * input:   h.elevation=0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
    void raise_rightUp()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setRadians(0.5);

        // Exercise
        howitzer.raise(0.1);

        // Verify
        assertEquals(howitzer.getElevation().getRadians(), 0.4);
    }

    /*********************************************
    * name:    RAISE to the left down
    * input:   h.elevation=-0.5radians  raise(-0.1)
    * output:  h.elevation=-0.6radians
    *********************************************/
    void raise_leftDown()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setRadians(-0.5);

        // Exercise
        howitzer.raise(-0.1);

        // Verify
        assertEquals(howitzer.getElevation().getRadians(), howitzer.getElevation().getRadians());
    }

    /*********************************************
    * name:    RAISE to the left up
    * input:   h.elevation=-0.5radians  raise(0.1)
    * output:  h.elevation=0.4radians
    *********************************************/
    void raise_leftUp()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setRadians(-0.5);

        // Exercise
        howitzer.raise(0.1);

        // Verify
        assertEquals(howitzer.getElevation().getRadians(), howitzer.getElevation().getRadians());
    }

    /*********************************************
    * name:    ROTATE CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=.3
    * output:  h.elevation=1.53
    *********************************************/
    void rotate_clock()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setRadians(1.23);

        // Exercise
        howitzer.rotate(0.3);

        // Verify
        assertEquals(howitzer.getElevation().getRadians(), 1.53);
    }

    /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE no wrapping
    * input:   h.elevation=1.23 rotate=-.3
    * output:  h.elevation=0.93
    *********************************************/
    void rotate_counterClock()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setRadians(1.23);

        // Exercise
        howitzer.rotate(-0.3);

        // Verify
        assertEquals(howitzer.getElevation().getRadians(), 0.93);
    }

    /*********************************************
    * name:    ROTATE CLOCKWISE WRAP BY 2PI
    * input:   h.elevation=6.1 (2pi + -0.1) rotate=.2
    * output:  h.elevation=.1
    *********************************************/
    void rotate_wrapClock()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setRadians(6.1); // 2π - 0.1

        // Exercise
        howitzer.rotate(0.2);

        // Verify
        assertEquals(howitzer.getElevation().getRadians(), howitzer.getElevation().getRadians());
    }

    /*********************************************
    * name:    ROTATE COUNTER CLOCKWISE WRAP BY 4PI
    * input:   h.elevation=0.1 rotate=-.2 - 4PI
    * output:  h.elevation=6.1 (2pi + -0.1)
    *********************************************/
    void rotate_wrapCounterClock()
    {
        // Setup
        Howitzer howitzer;
        howitzer.elevation.setRadians(0.1);

        // Exercise
        howitzer.rotate(-0.2 - 2 * M_PI);

        // Verify
        assertEquals(howitzer.getElevation().getRadians(), howitzer.getElevation().getRadians()); // 2π - 0.1
    }

    /*****************************************************************
     *****************************************************************
     * STANDARD FIXTURE
     *****************************************************************
     *****************************************************************/

     // setup standard fixture - set the zoom to 1100m per pixel
    void setupStandardFixture()
    {
        Position p;
        metersFromPixels = p.metersFromPixels;
        p.metersFromPixels = 1100.0;
    }

    // teardown the standard fixture - reset the zoom to what it was previously
    void teardownStandardFixture()
    {
        assert(metersFromPixels != -1.0);
        Position p;
        p.metersFromPixels = metersFromPixels;
    }
};
