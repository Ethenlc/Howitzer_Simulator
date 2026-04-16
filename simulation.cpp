/**********************************************************************
 * Source File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"

 /**********************************************************************
  * Simulator : CONSTRUCTOR
  * Initialize the simulator with a given position.
  **********************************************************************/
Simulator::Simulator(const Position& posUpperRight)
	: posUpperRight(posUpperRight), howitzer(), ground()
{
	// Set the initial position and size of the ground
	ground.setPosition(0, 0); // Or some appropriate value
	ground.setSize(posUpperRight.getMetersX(), 50); // Example size; adjust as needed

	// Initialize the howitzer
	howitzer.generatePosition(posUpperRight);
}

/**********************************************************************
 * Simulator : DRAW
 * Draw the ground and the howitzer.
 **********************************************************************/
void Simulator::draw(ogstream& gout, double flightTime) const
{
	// Draw the howitzer
	howitzer.draw(gout, flightTime);
}
