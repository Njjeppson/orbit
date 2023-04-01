/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "point.h"
#include "velocity.h"
#include "physics.h"
#include "position.h"
#include "direction.h"
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:

    Demo(Position ptUpperRight) :
        ptUpperRight(ptUpperRight), angleEarth(0.0)
    {
        ptHubble.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptHubble.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
        ptHubble.setMetersX(0.0);  // Hubble initial position in meters
        ptHubble.setMetersY(-42164000.0);
        vHubble.setDxDy(3100.0, 0.0);  // Hubble initial velocity in m/s

        ptSputnik.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptSputnik.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
        ptSputnik.setMetersX(-36515095.13);
        ptSputnik.setMetersY(21082000.0);
        vSputnik.setDxDy(2050.0, 2684.68);  // Sputnik initial velocity in m/s

        ptStarlink.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptStarlink.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
        ptStarlink.setMetersX(0.0);
        ptStarlink.setMetersY(-13020000.0);
        vStarlink.setDxDy(5800.0, 0.0);

        ptCrewDragon.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptCrewDragon.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
        ptCrewDragon.setMetersX(0.0);
        ptCrewDragon.setMetersY(8000000.0);
        vCrewDragon.setDxDy(-7900.0, 0.0);

        ptShip.setPixelsX(-450);
        ptShip.setPixelsY(450);
        
        ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
        ptGPS.setMetersX(0.0);
        ptGPS.setMetersY(26560000.0);
        vGPS.setDxDy(-3880.0, 0.0);

        ptGPS2.setMetersX(23001634.72);
        ptGPS2.setMetersY(13280000.0);
        vGPS2.setDxDy(-1940.00, 3360.18);

        ptGPS3.setMetersX(23001634.72);
        ptGPS3.setMetersY(-13280000.0);
        vGPS3.setDxDy(1940.00, 3360.18);

        ptGPS4.setMetersX(0.0);
        ptGPS4.setMetersY(-26560000.0);
        vGPS4.setDxDy(3880.0, 0.0);

        ptGPS5.setMetersX(-23001634.72);
        ptGPS5.setMetersY(-13280000.0);
        vGPS5.setDxDy(1940.00, -3360.18);

        ptGPS6.setMetersX(-23001634.72);
        ptGPS6.setMetersY(13280000.0);
        vGPS6.setDxDy(-1940.00, -3360.18);

        ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        angleShip = 0.0;
        angleEarth = 0.0;
        phaseStar = 0;
    }

    Acceleration shipAcc;
    Direction shipDir;

    Velocity vStarlink;
    Velocity vCrewDragon;
    Velocity vHubble;
    Velocity vSputnik;
    Velocity vGPS;
    Velocity vGPS2;
    Velocity vGPS3;
    Velocity vGPS4;
    Velocity vGPS5;
    Velocity vGPS6;
    Velocity vShip;

    Position ptHubble;
    Position ptSputnik;
    Position ptStarlink;
    Position ptCrewDragon;
    Position ptShip;
    Position ptEarth;
    Position ptGPS;
    Position ptGPS2;
    Position ptGPS3;
    Position ptGPS4;
    Position ptGPS5;
    Position ptGPS6;
    Position ptStar;
    Position ptUpperRight;
    Position ptShipFront;

    unsigned char phaseStar;

    double angleShip;
    double angleEarth;
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
    // the first step is to cast the void pointer into a game object. This
    // is the first step of every single callback function in OpenGL. 
    Demo* pDemo = (Demo*)p;
    Acceleration getGravity(const Position & posElement);
    Velocity& updateVelocity(Velocity & velocity, const Acceleration & acceleration, double time);
    Position& updatePosition(Position & pos, const Velocity & vel, const Acceleration & acc, double time);

    

    //move according to inertia
    double frameRate = 30.0;
    double hoursPerDay = 24.0;
    double minutesPerHour = 60.0;
    double secondsPerMinute = 60.0;
    double secondsPerDay = hoursPerDay * minutesPerHour * secondsPerMinute;
    double dilation = hoursPerDay * minutesPerHour;
    double t = dilation / frameRate;

    Acceleration gpsGravity = getGravity(pDemo->ptGPS);
    updatePosition(pDemo->ptGPS, pDemo->vGPS, gpsGravity, t);
    updateVelocity(pDemo->vGPS, gpsGravity, t);

    Acceleration gpsGravity2 = getGravity(pDemo->ptGPS2);
    updatePosition(pDemo->ptGPS2, pDemo->vGPS2, gpsGravity2, t);
    updateVelocity(pDemo->vGPS2, gpsGravity2, t);

    Acceleration gpsGravity3 = getGravity(pDemo->ptGPS3);
    updatePosition(pDemo->ptGPS3, pDemo->vGPS3, gpsGravity3, t);
    updateVelocity(pDemo->vGPS3, gpsGravity3, t);

    Acceleration gpsGravity4 = getGravity(pDemo->ptGPS4);
    updatePosition(pDemo->ptGPS4, pDemo->vGPS4, gpsGravity4, t);
    updateVelocity(pDemo->vGPS4, gpsGravity4, t);

    Acceleration gpsGravity5 = getGravity(pDemo->ptGPS5);
    updatePosition(pDemo->ptGPS5, pDemo->vGPS5, gpsGravity5, t);
    updateVelocity(pDemo->vGPS5, gpsGravity5, t);

    Acceleration gpsGravity6 = getGravity(pDemo->ptGPS6);
    updatePosition(pDemo->ptGPS6, pDemo->vGPS6, gpsGravity6, t);
    updateVelocity(pDemo->vGPS6, gpsGravity6, t);

    Acceleration dragonGravity = getGravity(pDemo->ptCrewDragon);
    updatePosition(pDemo->ptCrewDragon, pDemo->vCrewDragon, dragonGravity, t);
    updateVelocity(pDemo->vCrewDragon, dragonGravity, t);

    Acceleration starlinkGravity = getGravity(pDemo->ptStarlink);
    updatePosition(pDemo->ptStarlink, pDemo->vStarlink, starlinkGravity, t);
    updateVelocity(pDemo->vStarlink, starlinkGravity, t);

    //update Hubble
    Acceleration aGravityHubble = getGravity(pDemo->ptHubble);
    updatePosition(pDemo->ptHubble, pDemo->vHubble, aGravityHubble, t);
    updateVelocity(pDemo->vHubble, aGravityHubble, t);

    //update Sputnik
    Acceleration aGravitySputnik = getGravity(pDemo->ptSputnik);
    updatePosition(pDemo->ptSputnik, pDemo->vSputnik, aGravitySputnik, t);
    updateVelocity(pDemo->vSputnik, aGravitySputnik, t);

    //
    // accept input
    //

    Acceleration shipGravity = getGravity(pDemo->ptShip);
    updatePosition(pDemo->ptShip, pDemo->vShip, shipGravity, t);
    updateVelocity(pDemo->vShip, shipGravity, t);
    
    // move by a little
    updatePosition(pDemo->ptShip, pDemo->vShip, pDemo->shipAcc, t);
    if (pUI->isUp()) {
        updateVelocity(pDemo->vShip, pDemo->shipAcc, t);
    }
    if (pUI->isDown()) {
        updateVelocity(pDemo->vShip, pDemo->shipAcc, -t);
    }
    if (pUI->isLeft()) {
        pDemo->shipDir.rotate(-0.1);
        pDemo->shipAcc.setAccelerationDirection(1.0, pDemo->shipDir);
        pDemo->angleShip -= 0.1;
    }
    if (pUI->isRight()) {
        pDemo->shipDir.rotate(0.1);
        pDemo->shipAcc.setAccelerationDirection(1.0, pDemo->shipDir);
        pDemo->angleShip += 0.1;
    }
    if (pUI->isSpace())
        drawProjectile(pDemo->ptShipFront);

    //
    // perform all the game logic
    //

    // rotate the earth
    double radiansInADay = 3.14159 * 2.0;
    double radiansPerFrame = (radiansInADay / frameRate) * (dilation / secondsPerDay);
    pDemo->angleEarth += radiansPerFrame;
    // pDemo->angleShip += 0.02;
    pDemo->phaseStar++;

    //
    // draw everything
    //



    Position pt;

    // draw satellites
    drawCrewDragon(pDemo->ptCrewDragon, 0.0);
    drawStarlink(pDemo->ptStarlink, 0.0);
    drawShip(pDemo->ptShip, pDemo->angleShip, pUI->isDown());
    drawHubble(pDemo->ptHubble, 0.0);
    drawSputnik(pDemo->ptSputnik, 0.0);
    drawGPS(pDemo->ptGPS, 0.0);
    drawGPS(pDemo->ptGPS2, 0.0);
    drawGPS(pDemo->ptGPS3, 0.0);
    drawGPS(pDemo->ptGPS4, 0.0);
    drawGPS(pDemo->ptGPS5, 0.0);
    drawGPS(pDemo->ptGPS6, 0.0);

    // draw parts
    //pt.setPixelsX(pDemo->ptCrewDragon.getPixelsX() + 20);
    //pt.setPixelsY(pDemo->ptCrewDragon.getPixelsY() + 20);
    //drawCrewDragonRight(pt, pDemo->angleShip); // notice only two parameters are set
    //pt.setPixelsX(pDemo->ptHubble.getPixelsX() + 20);
    //pt.setPixelsY(pDemo->ptHubble.getPixelsY() + 20);
    //drawHubbleLeft(pt, pDemo->angleShip);      // notice only two parameters are set
    //pt.setPixelsX(pDemo->ptGPS.getPixelsX() + 20);
    //pt.setPixelsY(pDemo->ptGPS.getPixelsY() + 20);
    //drawGPSCenter(pt, pDemo->angleShip);       // notice only two parameters are set
    //pt.setPixelsX(pDemo->ptStarlink.getPixelsX() + 20);
    //pt.setPixelsY(pDemo->ptStarlink.getPixelsY() + 20);
    //drawStarlinkArray(pt, pDemo->angleShip);   // notice only two parameters are set

    // draw fragments
    //pt.setPixelsX(pDemo->ptSputnik.getPixelsX() + 20);
    //pt.setPixelsY(pDemo->ptSputnik.getPixelsY() + 20);
    //drawFragment(pt, pDemo->angleShip);
    //pt.setPixelsX(pDemo->ptShip.getPixelsX() + 20);
    //pt.setPixelsY(pDemo->ptShip.getPixelsY() + 20);
    //drawFragment(pt, pDemo->angleShip);

    // spawn stars
    drawStar(pDemo->ptStar, pDemo->phaseStar);



    // draw the earth
    pt.setMeters(0.0, 0.0);
    drawEarth(pDemo->ptEarth, pDemo->angleEarth);

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
    // Initialize OpenGL
    Position ptUpperRight;
    ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
    ptUpperRight.setPixelsX(1000.0);
    ptUpperRight.setPixelsY(1000.0);
    Interface ui(0, NULL,
        "Demo",   /* name on the window */
        ptUpperRight);

    // Initialize the demo
    Demo demo(ptUpperRight);

    // set everything into action
    ui.run(callBack, &demo);


    return 0;
}