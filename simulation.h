/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "howitzer.h"
#include "uiDraw.h"

 // forward declaration for the Ground unit tests
class TestGround;

/***********************************************************
 * GROUND
 * The ground class
 ***********************************************************/
class Ground
{
    // unit test access
    friend ::TestGround;

public:
    // the constructor generates the ground
    Ground(const Position& posUpperRight);
    Ground() : ground(nullptr), iHowitzer(0), iTarget(0), position(0, 0), width(0), height(0) {}

    // reset the game
    void reset(Position& posHowitzer);

    // draw the ground on the screen
    void draw(ogstream& gout) const;

    // determine how high the Point is off the ground
    double getElevationMeters(const Position& pos) const;

    // where the target is located?
    Position getTarget() const;

    // Set the position and size of the ground
    void setPosition(double x, double y) { position.setMeters(x, y); }
    void setSize(double width, double height) { this->width = width; this->height = height; }

    // Get the position of the ground
    Position getPosition() const { return position; }

    // Get the height of the ground
    double getHeight() const { return height; }

private:
    double* ground;               // elevation of the ground, in pixels 
    int iTarget;                   // the location of the target, in pixels
    int iHowitzer;                 // the location of the howitzer
    Position posUpperRight;        // size of the screen
    Position position;             // Position of the ground
    double width;                  // Width of the ground
    double height;                 // Height of the ground
};

/*********************************************
 * Simulator
 * Execute one simulation of a projectile being fired.
 *********************************************/
class Simulator
{
public:
    Simulator(const Position& posUpperRight);

    // Draw the simulation components
    void draw(ogstream& gout, double flightTime) const;

private:
    Position posUpperRight; // The upper right corner of the simulation area
    Howitzer howitzer;      // The howitzer
    Ground ground;          // The ground object
};
