#define _USE_MATH_DEFINES
#pragma once

#include <iostream>
#include <cassert>
#include <math.h>
#include "Lab07.cpp"
#include "rotation.cpp"

using namespace std;

/*******************************
 * TEST Rotation
 * A class which contains the Rotation unit tests
 ********************************/
class TestRotation {

public:

	//Run all tests
	void run(Demo* pdemo, Rotation rotation) {
		testShipLeft(pdemo, rotation);
		testShipRight(pdemo, rotation);
		testShipLeftHold(pdemo, rotation);
		testShipRightHold(pdemo, rotation);
		testShipLeftLoop(pdemo, rotation);
		testShipRightLoop(pdemo, rotation);
		testFragment(pdemo, rotation);
		testEarth(pdemo, rotation);
	}

private:

	//Test pressing the left key
	void testShipLeft(Demo* pdemo, Rotation rotation) {
		//Setup
		pdemo->angleShip = 0.0;
		//Exercise
		rotation.shipRLeft(pdemo->angleShip);
		//Verify
		assert(pdemo->angleShip = -0.1);
		//Teardown
		pdemo->angleShip = 0.0;
	}

	//Test pressing the right key
	void testShipRight(Demo* pdemo, Rotation rotation) {
		//Setup
		pdemo->angleShip = 0.0;
		//Exercise
		rotation.shipRRight(pdemo->angleShip);
		//Verify
		assert(pdemo->angleShip = 0.1);
		//Teardown
		pdemo->angleShip = 0.0;
	}

	//Test holding down the left key
	void testShipLeftHold(Demo* pdemo, Rotation rotation) {
		//Setup
		pdemo->angleShip = 0.0;
		//Exercise
		for (int i = 0; i <= 5; i++) {
			rotation.shipRLeft(pdemo->angleShip);
		}
		//Verify
		assert(pdemo->angleShip = -0.5);
		//Teardown
		pdemo->angleShip = 0.0;
	}

	//Test holding down the right key
	void testShipRightHold(Demo* pdemo, Rotation rotation) {
		//Setup
		pdemo->angleShip = 0.0;
		//Exercise
		for (int i = 0; i <= 5; i++) {
			rotation.shipRRight(pdemo->angleShip);
		}
		//Verify
		assert(pdemo->angleShip = 0.5);
		//Teardown
		pdemo->angleShip = 0.0;
	}

	//Test ship angle looping around upon reaching -PI radians
	void testShipLeftLoop(Demo* pdemo, Rotation rotation) {
		//Setup
		pdemo->angleShip = -M_PI + 0.05;
		//Exercise
		rotation.shipRLeft(pdemo->angleShip);
		//Verify
		assert(pdemo->angleShip = M_PI - 0.05);
		//Teardown
		pdemo->angleShip = 0.0;
	}

	//Test ship angle looping around upon reaching PI radians
	void testShipRightLoop(Demo* pdemo, Rotation rotation) {
		//Setup
		pdemo->angleShip = M_PI - 0.05;
		//Exercise
		rotation.shipRRight(pdemo->angleShip);
		//Verify
		assert(pdemo->angleShip = -M_PI + 0.05);
		//Teardown
		pdemo->angleShip = 0.0;
	}

	//Test fragment spinning wildly
	void testFragment(Demo* pdemo, Rotation rotation) {
		//Setup
		pdemo->angleFragment = 0.0;
		//Exercise
		for (int i = 0; i <= 5; i++) {
			double prev = pdemo->angleFragment;
			rotation.fragmentRRight(pdemo->angleFragment);

			//Verify
			assert(pdemo->angleShip > prev + 0.5 || pdemo->angleShip < prev - 0.5);
		}
		//Teardown
		pdemo->angleFragment = 0.0;
	}

	//Test earth rotation
	void testEarth(Demo* pdemo, Rotation rotation) {
		//Setup
		pdemo->angleEarth = 0.0;
		//Exercise
		rotation.rotateEarth(pdemo->angleEarth);
		//Verify
		assert(pdemo->angleEarth = 0.0034906556);
		//Teardown
		pdemo->angleEarth = 0.0;
	}
};