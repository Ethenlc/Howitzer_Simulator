/***********************************************************************
 * Header File:
 *    ACCELERATION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about acceleration
 ************************************************************************/

#pragma once

class TestAcceleration;
class TestVelocity;
class TestPosition;
class TestLander;
class Angle;

/*********************************************
 * Acceleration
 * Let's get moving
 *********************************************/
class Acceleration
{
	friend TestPosition;
	friend TestVelocity;
	friend TestAcceleration;
	friend TestLander;

public:
	// constructors
	Acceleration() : ddx(0.0), ddy(0.0) { }
	Acceleration(double ddx, double ddy) : ddx(ddx), ddy(ddy) { }

	// getters
	double getDDX() const { return ddx; }
	double getDDY() const { return ddy; }

	// setters                        
	void setDDX(double ddx) { this->ddx = ddx; }
	void setDDY(double ddy) { this->ddy = ddy; }
	void set(const Angle& a, double magnitude);

	// adders
	void addDDX(double ddx);
	void addDDY(double ddy);
	void add(const Acceleration& other);

	// additional setters for test cases
	void ax(double ax) { this->ddx = ax; }
	void ay(double ay) { this->ddy = ay; }

private:
	double ddx;     // horizontal acceleration
	double ddy;     // vertical acceleration
};
