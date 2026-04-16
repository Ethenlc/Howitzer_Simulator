/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#include <cassert>

Position::Position(double x, double y) : x(x), y(y), accelerationX(0.0), accelerationY(0.0) {}


/******************************************
 * POINT : ASSIGNMENT
 * Assign a point. Please look ahead to
 * Week 12 C++ reading for an idea of how this works.
 * Basically, we are copying the data from posRHS
 * into this.
 *****************************************/
Position& Position::operator=(const Position& pt)
{
    x = pt.x;
    y = pt.y;
    accelerationX = pt.accelerationX;
    accelerationY = pt.accelerationY;
    return *this;
}

void Position::setMeters(double xMeters, double yMeters)
{
    x = xMeters;
    y = yMeters;
}

void Position::setMetersX(double xMeters)
{
    x = xMeters;
}

void Position::setMetersY(double yMeters)
{
    y = yMeters;
}

double Position::getZoom() const
{
    return metersFromPixels;
}

void Position::setZoom(double zoomFactor)
{
    assert(zoomFactor != 0);
    metersFromPixels = zoomFactor;
}

double Position::getPixelsX() const
{
    return x / metersFromPixels;
}

double Position::getPixelsY() const
{
    return y / metersFromPixels;
}

void Position::setPixelsX(double pixels)
{
    x = pixels * metersFromPixels;
}

void Position::setPixelsY(double pixels)
{
    y = pixels * metersFromPixels;
}

double Position::addMetersX(double dx)
{
    x += dx;
    return x;
}

double Position::addMetersY(double dy)
{
    y += dy;
    return y;
}

double Position::addPixelsX(double dp)
{
    x += dp * metersFromPixels;
    return x;
}

double Position::addPixelsY(double dp)
{
    y += dp * metersFromPixels;
    return y;
}

void Position::reverse()
{
    x = -x;
    y = -y;
}

void Position::update(const Acceleration& a, const Velocity& v, double t)
{
    x += v.getDX() * t + 0.5 * a.getDDX() * t * t;
    y += v.getDY() * t + 0.5 * a.getDDY() * t * t;
}

/************************************************************************
 * UPDATE POSITION
 * Update the current position based on the impulse of velocity
 * taking into account time dilation:
 *
 *   s = s_0 + vt + 1/2 at^2
 *
 *   INPUT  POSITION     The location of the item
 *          VELOCITY     The velocity of the item
 *          ACCELERATION The acceleration of the item
 *          TIME         How much time are we talking about?
 *   OUTPUT POSITION     The location, updated
 *
 *
 *  x = x + dx t + 1/2 ddx t^2
 *  y = y + dy t + 1/2 ddy t^2
 *************************************************************************/
void Position::add(const Acceleration& a, const Velocity& v, double t)
{
    update(a, v, t);
}

void Position::ax(double ax)
{
    accelerationX = ax;
}

void Position::ay(double ay)
{
    accelerationY = ay;
}

/******************************************
 * POSITION insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream& operator<<(std::ostream& out, const Position& pt)
{
    out << "(" << pt.getMetersX() << "m , " << pt.getMetersY() << "m)";
    return out;
}

/*******************************************
* POSITION extraction
*       Prompt for coordinates
******************************************/
std::istream& operator>>(std::istream& in, Position& pt)
{
    double x, y;
    in >> x >> y;

    pt.setMetersX(x);
    pt.setMetersY(y);

    return in;
}
