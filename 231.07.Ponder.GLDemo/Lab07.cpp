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
        //ptHubble.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        //ptHubble.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        //ptSputnik.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        //ptSputnik.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        //ptStarlink.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        //ptStarlink.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        //ptCrewDragon.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        //ptCrewDragon.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        //ptShip.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        //ptShip.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
        //ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        //ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
        ptGPS.setMetersX(0.0);
        ptGPS.setMetersY(42164000.0);
        vGPS.setDxDy(3100.0, 0.0);
        //ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        //ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        //angleShip = 0.0;
        //angleEarth = 0.0;
        //phaseStar = 0;
    }
    Velocity vGPS;
    Position ptEarth;

    //Position ptHubble;
    //Position ptSputnik;
    //Position ptStarlink;
    //Position ptCrewDragon;
    //Position ptShip;
    Position ptGPS;
    //Position ptStar;
    Position ptUpperRight;

    unsigned char phaseStar;

    //double angleShip;
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

    //
    // accept input
    //

    // move by a little
    //if (pUI->isUp())
    //    pDemo->ptShip.addPixelsY(1.0);
    //if (pUI->isDown())
    //    pDemo->ptShip.addPixelsY(-1.0);
    //if (pUI->isLeft())
    //    pDemo->ptShip.addPixelsX(-1.0);
    //if (pUI->isRight())
    //    pDemo->ptShip.addPixelsX(1.0);

    //move according to inertia
    double frameRate = 30.0;
    double hoursPerDay = 24.0;
    double minutesPerHour = 60.0;
    double secondsPerMinute = 60.0;
    double secondsPerDay = hoursPerDay * minutesPerHour * secondsPerMinute;
    double dilation = hoursPerDay * minutesPerHour;
    double t = dilation / frameRate;
    Acceleration aGravity = getGravity(pDemo->ptGPS);
    updatePosition(pDemo->ptGPS, pDemo->vGPS, aGravity, t);
    updateVelocity(pDemo->vGPS, aGravity, t);



    //
    // perform all the game logic
    //

    // rotate the earth
    double radiansInADay = 3.14159 * 2.0;
    double radiansPerFrame = (radiansInADay / frameRate) * (dilation / secondsPerDay);
    pDemo->angleEarth += radiansPerFrame;
    //pDemo->angleShip += 0.02;
    //pDemo->phaseStar++;


    //
    // draw everything
    //



    //Position pt;

    // draw satellites
    //drawCrewDragon(pDemo->ptCrewDragon, pDemo->angleShip);
    //drawHubble(pDemo->ptHubble, pDemo->angleShip);
    //drawSputnik(pDemo->ptSputnik, pDemo->angleShip);
    //drawStarlink(pDemo->ptStarlink, pDemo->angleShip);
    //drawShip(pDemo->ptShip, pDemo->angleShip, pUI->isSpace());
    drawGPS(pDemo->ptGPS, 0.0);

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

    // draw a single star
    //drawStar(pDemo->ptStar, pDemo->phaseStar);

    // draw the earth
    //pt.setMeters(0.0, 0.0);
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