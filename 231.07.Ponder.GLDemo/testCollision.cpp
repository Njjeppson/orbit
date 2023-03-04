#include "collision.h"
#include <cmath>
#include <gtest/gtest.h>

// Test the Collision class
TEST(CollisionTest, TestCollision)
{
	// Define two objects with positions and radii
	Object obj1(0, 0, 5);
	Object obj2(10, 0, 5);

	// Test the collision function for no collision
	ASSERT_FALSE(Collision::detectCollision(obj1, obj2));

	// Move obj2 so it collides with obj1
	obj2.setX(3);

	// Test the collision function for collision
	ASSERT_TRUE(Collision::detectCollision(obj1, obj2));
}

// Test the Object class
TEST(ObjectTest, TestObject)
{
	// Define an object with a position and radius
	Object obj(0, 0, 5);

	// Test the getters and setters for position and radius
	ASSERT_EQ(obj.getX(), 0);
	ASSERT_EQ(obj.getY(), 0);
	ASSERT_EQ(obj.getRadius(), 5);

	obj.setX(10);
	obj.setY(20);
	obj.setRadius(15);

	ASSERT_EQ(obj.getX(), 10);
	ASSERT_EQ(obj.getY(), 20);
	ASSERT_EQ(obj.getRadius(), 15);
}