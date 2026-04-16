/***********************************************************************
 * Source File:
 *    MAIN
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Launches the unit tests - that is all!
 ************************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "simulation.h" // for GROUND
#include "position.h"   // for POSITION
#include "test.h"       // for TEST
#include "velocity.h"   // for VELOCITY
#include "projectile.h" // for PROJECTILE
#include "angle.h"      // for ANGLE
#include <vector>

using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
    Demo(Position ptUpperRight) :
        ptUpperRight(ptUpperRight),
        ground(ptUpperRight),
        time(0.0),
        angle(0.0),
        projectileActive(false)
    {
        // Set the horizontal position of the howitzer. This should be random.
        ptHowitzer.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);

        // Generate the ground and set the vertical position of the howitzer.
        ground.reset(ptHowitzer);
    }

    Ground ground;             // the ground
    Position ptHowitzer;       // location of the howitzer
    Position ptUpperRight;     // size of the screen
    double angle;              // angle of the howitzer 
    double time;               // amount of time since the last firing
    bool projectileActive;     // whether a projectile is active
    Projectile projectile;     // projectile object
    string centerMessage;

    std::vector<Position> projectileTrail;
    std::vector<double> trailAges; // Stores the age of each trail point
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    Demo* pDemo = (Demo*)p;

    // Initialize the gout variable for displaying messages
    ogstream gout(Position(pDemo->ptUpperRight.getMetersX() / 2, pDemo->ptUpperRight.getMetersY() / 2));
    gout << pDemo->centerMessage;

    // Accept input
    if (pUI->isRight())
        pDemo->angle += 1.5;
    if (pUI->isLeft())
        pDemo->angle -= 1.5;

    if (pUI->isUp())
        pDemo->angle += (pDemo->angle >= 0 ? -0.25 : 0.25);
    if (pUI->isDown())
        pDemo->angle += (pDemo->angle >= 0 ? 0.25 : -0.25);

    if (pUI->isSpace() && !pDemo->projectileActive)
    {
        pDemo->time = 0.0;
        pDemo->projectileActive = true;
        pDemo->centerMessage = ""; // Reset the message

        Angle angle(pDemo->angle);
        pDemo->projectile.fire(angle, pDemo->ptHowitzer, 827.0);

        // Clear the trail
        pDemo->projectileTrail.clear();
    }

    // Perform all the game logic
    if (pDemo->projectileActive)
    {
        pDemo->time += 0.5;
    }

    if (pDemo->projectileActive)
    {
        pDemo->projectile.advance(0.5);

        // Get the current projectile position
        Position currentPos = pDemo->projectile.getCurrentPosition();

        // Add the current position to the trail
        pDemo->projectileTrail.push_back(currentPos);

        // Check if the projectile hits the target
        Position targetPosition = pDemo->ground.getTarget();
        double targetRadius = 250.0;
        if ((currentPos.getMetersX() > targetPosition.getMetersX() - targetRadius) &&
            (currentPos.getMetersX() < targetPosition.getMetersX() + targetRadius) &&
            (currentPos.getMetersY() > targetPosition.getMetersY() - targetRadius) &&
            (currentPos.getMetersY() < targetPosition.getMetersY() + targetRadius))
        {
            pDemo->projectileActive = false;
            pDemo->centerMessage = "Target hit";
            std::cout << "Target hit at: (" << currentPos.getMetersX() << ", " << currentPos.getMetersY() << ")\n";
        }
        // Check if the projectile has fallen below the ground level at its current X position
        else if (currentPos.getMetersY() <= pDemo->ground.getElevationMeters(currentPos))
        {
            pDemo->projectileActive = false;
            pDemo->centerMessage = "Ground hit";
            std::cout << "Ground hit at: (" << currentPos.getMetersX() << ", " << currentPos.getMetersY() << ")\n";
        }
        // Check if the projectile is out of bounds (hits the sides)
        else if (currentPos.getMetersX() < 0 || currentPos.getMetersX() > pDemo->ptUpperRight.getMetersX())
        {
            pDemo->projectileActive = false;
            pDemo->centerMessage = "Out of bounds";
            std::cout << "Out of bounds at: (" << currentPos.getMetersX() << ", " << currentPos.getMetersY() << ")\n";
        }
    }

    // Draw everything
    gout.setPosition(Position(10.0, pDemo->ptUpperRight.getPixelsY() - 20.0));

    // Draw the ground
    pDemo->ground.draw(gout);

    // Draw the howitzer
    gout.drawHowitzer(pDemo->ptHowitzer, (pDemo->angle * 3.14159 / 180), pDemo->time);

    // Draw the projectile trail
    for (size_t i = 0; i < pDemo->projectileTrail.size(); ++i)
    {
        Position trailPos = pDemo->projectileTrail[i];
        double age = pDemo->time - (i * 0.5); // Age of the trail segment
        gout.drawProjectile(trailPos, age);

        gout.drawSmallProjectile(trailPos, 0.0);
    }

    // Draw the projectile if it's active
    if (pDemo->projectileActive)
    {
        Position pos = pDemo->projectile.getCurrentPosition();
        // Draw the projectile with maximum brightness
        gout.drawProjectile(pos, 0.0);
    }

    // Draw some text on the screen
    gout.setf(ios::fixed | ios::showpoint);
    gout.precision(1);
    gout.setPosition(Position(pDemo->ptUpperRight.getMetersX() / 1.35, pDemo->ptUpperRight.getMetersY() - 600));
    gout << "Time since the bullet was fired: " << pDemo->time << "s\n";

    // Draw the center message
    gout.setPosition(Position(pDemo->ptUpperRight.getMetersX() / 2, pDemo->ptUpperRight.getMetersY() / 2));
    gout << pDemo->centerMessage;
}


double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ PWSTR pCmdLine,
    _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Run Test Cases
    testRunner();

    // Initialize OpenGL
    Position ptUpperRight;
    ptUpperRight.setPixelsX(700.0);
    ptUpperRight.setPixelsY(500.0);
    Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
    Interface ui(0, NULL,
        "Demo",   /* name on the window */
        ptUpperRight);

    // Initialize the demo
    Demo demo(ptUpperRight);

    // set everything into action
    ui.run(callBack, &demo);

    return 0;
}
