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
#include "position.h"      // for POINT
#include "physics.h"
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
    Demo(Position ptUpperRight) :
        ptUpperRight(ptUpperRight)
    {


        ptGPS.setMeters(0.0, 42164000.0);


        ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        angleShip = 0.0;
        angleEarth = 0.0;
        phaseStar = 0;
    }

    Position ptHubble;
    Position ptSputnik;
    Position ptStarlink;
    Position ptCrewDragon;
    Position ptShip;
    Position ptGPS;
    Position ptStar;
    Position ptUpperRight;

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

    //
    // accept input
    //

    // move by a little
    if (pUI->isUp())
        pDemo->ptShip.addPixelsY(1.0);
    if (pUI->isDown())
        pDemo->ptShip.addPixelsY(-1.0);
    if (pUI->isLeft())
        pDemo->ptShip.addPixelsX(-1.0);
    if (pUI->isRight())
        pDemo->ptShip.addPixelsX(1.0);


    //
    // perform all the game logic
    //

    // rotate the earth
    pDemo->angleEarth += 0.01;
    pDemo->angleShip += 0.02;
    pDemo->phaseStar++;

    //
    // draw everything
    //

    Position pt;

    // draw satellites
    drawCrewDragon(pDemo->ptCrewDragon, pDemo->angleShip);
    drawHubble(pDemo->ptHubble, pDemo->angleShip);
    drawSputnik(pDemo->ptSputnik, pDemo->angleShip);
    drawStarlink(pDemo->ptStarlink, pDemo->angleShip);
    drawShip(pDemo->ptShip, pDemo->angleShip, pUI->isSpace());
    drawGPS(pDemo->ptGPS, pDemo->angleShip);



    // draw a single star
    drawStar(pDemo->ptStar, pDemo->phaseStar);

    // draw the earth
    pt.setMeters(0.0, 0.0);
    drawEarth(pt, pDemo->angleEarth);

    double x = 42164.0, y = 0.0, vx = 0.0, vy = 3074.0, m = 1.0;
    int numsteps = 1000;
    double time_step = 1.0; // time step in seconds
    Physics phys;

    phys.simulate(time_step, numsteps, x, y, vx, vy, m);

    // print final position and velocity
    cout << "Final position: (" << x << ", " << y << ")" << endl;
    cout << "Final velocity: (" << vx << ", " << vy << ")" << endl;
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

//okay
