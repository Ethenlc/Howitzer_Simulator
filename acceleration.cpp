/***********************************************************************
 * Source File:
 *    ACCELERATION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"
#include <cmath>

 /*********************************************
  * ACCELERATION : SET
  *  set from angle and direction
  *********************************************/
void Acceleration::set(const Angle& a, double magnitude)
{
	ddx = magnitude * sin(a.getRadians());
	ddy = magnitude * cos(a.getRadians());
}

/*********************************************
 * ACCELERATION : ADD DDX
 *  add to horizontal acceleration
 *********************************************/
void Acceleration::addDDX(double ddx)
{
	this->ddx += ddx;
}

/*********************************************
 * ACCELERATION : ADD DDY
 *  add to vertical acceleration
 *********************************************/
void Acceleration::addDDY(double ddy)
{
	this->ddy += ddy;
}

/*********************************************
 * ACCELERATION : ADD
 *  add another acceleration
 *********************************************/
void Acceleration::add(const Acceleration& other)
{
	this->ddx += other.ddx;
	this->ddy += other.ddy;
}
