/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/


#pragma once

#include <iostream>
#include <cmath>

class TestPosition;
class Acceleration;
class Velocity;
class TestGround;
class TestHowitzer;
class TestProjectile;

/*********************************************
 * Position
 * A single position on the field in Meters
 *********************************************/
class Position
{
public:
    friend ::TestPosition;
    friend ::TestGround;
    friend ::TestHowitzer;
    friend ::TestProjectile;

    // constructors
    Position() : x(0.0), y(0.0), accelerationX(0.0), accelerationY(0.0) {}
    Position(double x, double y);
    Position(const Position& pt) : x(pt.x), y(pt.y), accelerationX(pt.accelerationX), accelerationY(pt.accelerationY) {}
    Position& operator=(const Position& pt);

    // getters
    double getMetersX() const { return x; }
    double getMetersY() const { return y; }
    double getZoom() const;

    // setters
    void setMeters(double xMeters, double yMeters);
    void setMetersX(double xMeters);
    void setMetersY(double yMeters);
    void setPixelsX(double pixels);
    void setPixelsY(double pixels);
    void setZoom(double zoomFactor);

    // pixels to meters conversion
    double getPixelsX() const;
    double getPixelsY() const;

    // addition methods
    double addMetersX(double dx);
    double addMetersY(double dy);
    double addPixelsX(double dp);
    double addPixelsY(double dp);

    // other methods
    void reverse();

    // update position with acceleration and velocity
    void update(const Acceleration& a, const Velocity& v, double t);
    void add(const Acceleration& a, const Velocity& v, double t);

    // acceleration components
    void ax(double ax);
    void ay(double ay);

    // static member variable
    static double metersFromPixels;

private:
    double x;  // horizontal position
    double y;  // vertical position
    double accelerationX;  // acceleration in x direction
    double accelerationY;  // acceleration in y direction
};

// stream I/O useful for debugging
std::ostream& operator<<(std::ostream& out, const Position& pt);
std::istream& operator>>(std::istream& in, Position& pt);

/*********************************************
 * PT
 * Trivial point
 *********************************************/
struct PT
{
    double x;
    double y;
};
