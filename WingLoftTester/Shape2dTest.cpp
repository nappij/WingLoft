// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#define _USE_MATH_DEFINES

#include "Shape2d.h"
#include "TestHarness.h"

// Global tolerance value
const static double TOL = 1.0e-6;

// Degrees to Radians conversion factor
const static double DEG_TO_RAD = M_PI / 180.0;

// *****************************************************************************
// Constructor Tests
// *****************************************************************************
TEST(defaultConstructor, Shape2d)
{
	Shape2d myShape;
	CHECK_EQUAL(0, myShape.getPoints().size());
}

TEST(valueConstructor, Shape2d)
{
	// Define points
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(1.0, 1.0, 0.0));
	myPoints.push_back(Vector3(1.0, -1.0, 0.0));
	myPoints.push_back(Vector3(-1.0, -1.0, 0.0));
	myPoints.push_back(Vector3(-1.0, 1.0, 0.0));
	
	// Make shape
	Shape2d myShape(myPoints);

	CHECK_EQUAL(4, myShape.getPoints().size());
	for (size_t i = 0; i < myShape.getPoints().size(); ++i)
	{
		CHECK_DOUBLES_EQUAL(myPoints[i].x, myShape[i].x, 0.0);
		CHECK_DOUBLES_EQUAL(myPoints[i].y, myShape[i].y, 0.0);
		CHECK_DOUBLES_EQUAL(myPoints[i].z, myShape[i].z, 0.0);
	}
}

TEST(copyConstructor, Shape2d)
{
	// Define points
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(1.0, 1.0, 0.0));
	myPoints.push_back(Vector3(1.0, -1.0, 0.0));
	myPoints.push_back(Vector3(-1.0, -1.0, 0.0));
	myPoints.push_back(Vector3(-1.0, 1.0, 0.0));

	// Make shapes
	Shape2d myShape1(myPoints);
	Shape2d myShape2(myShape1);

	CHECK_EQUAL(myShape1.getPoints().size(), myShape2.getPoints().size());
	for (size_t i = 0; i < myShape1.getPoints().size(); ++i)
	{
		CHECK_DOUBLES_EQUAL(myShape1[i].x, myShape2[i].x, 0.0);
		CHECK_DOUBLES_EQUAL(myShape1[i].y, myShape2[i].y, 0.0);
		CHECK_DOUBLES_EQUAL(myShape1[i].z, myShape2[i].z, 0.0);
	}
}

// *****************************************************************************
// Assignment test
// *****************************************************************************
TEST(assignment, Shape2d)
{
	// Define points
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(1.0, 1.0, 0.0));
	myPoints.push_back(Vector3(1.0, -1.0, 0.0));
	myPoints.push_back(Vector3(-1.0, -1.0, 0.0));
	myPoints.push_back(Vector3(-1.0, 1.0, 0.0));

	// Make shapes
	Shape2d myShape1(myPoints);
	Shape2d myShape2;

	// Assignment
	myShape2 = myShape1;

	CHECK_EQUAL(myShape1.getPoints().size(), myShape2.getPoints().size());
	for (size_t i = 0; i < myShape1.getPoints().size(); ++i)
	{
		CHECK_DOUBLES_EQUAL(myShape1[i].x, myShape2[i].x, 0.0);
		CHECK_DOUBLES_EQUAL(myShape1[i].y, myShape2[i].y, 0.0);
		CHECK_DOUBLES_EQUAL(myShape1[i].z, myShape2[i].z, 0.0);
	}
}

// *****************************************************************************
// Compound operator tests
// *****************************************************************************
TEST(plusEqualsShape2d, Shape2d)
{
	// Define shape1
	std::vector<Vector3> myPoints1;
	myPoints1.push_back(Vector3(2.0, 1.0, 0.0));
	myPoints1.push_back(Vector3(1.0, -2.0, 0.0));
	Shape2d myShape1(myPoints1);

	// Define shape2
	std::vector<Vector3> myPoints2;
	myPoints2.push_back(Vector3(0.0, 2.0, 2.0));
	Shape2d myShape2(myPoints2);

	// Different size, should return myShape1
	myShape1 += myShape2;

	CHECK_EQUAL(2, myShape1.getPoints().size());
	for (size_t i = 0; i < myShape1.getPoints().size(); ++i)
	{
		CHECK_DOUBLES_EQUAL(myPoints1[i].x, myShape1[i].x, 0.0);
		CHECK_DOUBLES_EQUAL(myPoints1[i].y, myShape1[i].y, 0.0);
		CHECK_DOUBLES_EQUAL(myPoints1[i].z, myShape1[i].z, 0.0);
	}

	// Add a new point to myShape2 and try again.
	myPoints2.push_back(Vector3(0.0, -2.0, 2.0));
	myShape2 = Shape2d(myPoints2);

	myShape1 += myShape2;
	CHECK_DOUBLES_EQUAL(2.0, myShape1[0].x, 0.0);
	CHECK_DOUBLES_EQUAL(3.0, myShape1[0].y, 0.0);
	CHECK_DOUBLES_EQUAL(2.0, myShape1[0].z, 0.0);
	CHECK_DOUBLES_EQUAL(1.0, myShape1[1].x, 0.0);
	CHECK_DOUBLES_EQUAL(-4.0, myShape1[1].y, 0.0);
	CHECK_DOUBLES_EQUAL(2.0, myShape1[1].z, 0.0);
}

TEST(plusEqualsVector3, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(2.0, 1.0, 0.0));
	myPoints.push_back(Vector3(1.0, -2.0, 1.0));
	Shape2d myShape(myPoints);

	// Define point
	Vector3 point(2.0, -1.0, 1.0);

	myShape += point;

	CHECK_DOUBLES_EQUAL(4.0, myShape[0].x, 0.0);
	CHECK_DOUBLES_EQUAL(0.0, myShape[0].y, 0.0);
	CHECK_DOUBLES_EQUAL(1.0, myShape[0].z, 0.0);
	CHECK_DOUBLES_EQUAL(3.0, myShape[1].x, 0.0);
	CHECK_DOUBLES_EQUAL(-3.0, myShape[1].y, 0.0);
	CHECK_DOUBLES_EQUAL(2.0, myShape[1].z, 0.0);
}

TEST(minusEqualsShape2d, Shape2d)
{
	// Define shape1
	std::vector<Vector3> myPoints1;
	myPoints1.push_back(Vector3(2.0, 1.0, 0.0));
	myPoints1.push_back(Vector3(1.0, -2.0, 0.0));
	Shape2d myShape1(myPoints1);

	// Define shape2
	std::vector<Vector3> myPoints2;
	myPoints2.push_back(Vector3(0.0, 2.0, 2.0));
	Shape2d myShape2(myPoints2);

	// Different size, should return myShape1
	myShape1 -= myShape2;

	CHECK_EQUAL(2, myShape1.getPoints().size());
	for (size_t i = 0; i < myShape1.getPoints().size(); ++i)
	{
		CHECK_DOUBLES_EQUAL(myPoints1[i].x, myShape1[i].x, 0.0);
		CHECK_DOUBLES_EQUAL(myPoints1[i].y, myShape1[i].y, 0.0);
		CHECK_DOUBLES_EQUAL(myPoints1[i].z, myShape1[i].z, 0.0);
	}

	// Subtract a new point from myShape2 and try again.
	myPoints2.push_back(Vector3(0.0, -2.0, 2.0));
	myShape2 = Shape2d(myPoints2);

	myShape1 -= myShape2;
	CHECK_DOUBLES_EQUAL(2.0, myShape1[0].x, 0.0);
	CHECK_DOUBLES_EQUAL(-1.0, myShape1[0].y, 0.0);
	CHECK_DOUBLES_EQUAL(-2.0, myShape1[0].z, 0.0);
	CHECK_DOUBLES_EQUAL(1.0, myShape1[1].x, 0.0);
	CHECK_DOUBLES_EQUAL(0.0, myShape1[1].y, 0.0);
	CHECK_DOUBLES_EQUAL(-2.0, myShape1[1].z, 0.0);
}

TEST(minusEqualsVector3, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(2.0, 1.0, 0.0));
	myPoints.push_back(Vector3(1.0, -2.0, 1.0));
	Shape2d myShape(myPoints);

	// Define point
	Vector3 point(2.0, -1.0, 1.0);

	myShape -= point;

	CHECK_DOUBLES_EQUAL(0.0, myShape[0].x, 0.0);
	CHECK_DOUBLES_EQUAL(2.0, myShape[0].y, 0.0);
	CHECK_DOUBLES_EQUAL(-1.0, myShape[0].z, 0.0);
	CHECK_DOUBLES_EQUAL(-1.0, myShape[1].x, 0.0);
	CHECK_DOUBLES_EQUAL(-1.0, myShape[1].y, 0.0);
	CHECK_DOUBLES_EQUAL(0.0, myShape[1].z, 0.0);
}

TEST(timesEquals, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(2.0, 1.0, 0.0));
	myPoints.push_back(Vector3(1.0, -2.0, 1.0));
	Shape2d myShape(myPoints);

	// Define scalar
	double scalar = 2.0;

	myShape *= scalar;

	CHECK_DOUBLES_EQUAL(4.0, myShape[0].x, 0.0);
	CHECK_DOUBLES_EQUAL(2.0, myShape[0].y, 0.0);
	CHECK_DOUBLES_EQUAL(0.0, myShape[0].z, 0.0);
	CHECK_DOUBLES_EQUAL(2.0, myShape[1].x, 0.0);
	CHECK_DOUBLES_EQUAL(-4.0, myShape[1].y, 0.0);
	CHECK_DOUBLES_EQUAL(2.0, myShape[1].z, 0.0);
}

TEST(divideEquals, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(2.0, 1.0, 0.0));
	myPoints.push_back(Vector3(1.0, -2.0, 1.0));
	Shape2d myShape(myPoints);

	// Define scalar
	double scalar = 2.0;

	myShape /= scalar;

	CHECK_DOUBLES_EQUAL(1.0, myShape[0].x, 0.0);
	CHECK_DOUBLES_EQUAL(0.5, myShape[0].y, 0.0);
	CHECK_DOUBLES_EQUAL(0.0, myShape[0].z, 0.0);
	CHECK_DOUBLES_EQUAL(0.5, myShape[1].x, 0.0);
	CHECK_DOUBLES_EQUAL(-1.0, myShape[1].y, 0.0);
	CHECK_DOUBLES_EQUAL(0.5, myShape[1].z, 0.0);
}

// *****************************************************************************
// Unary operator tests
// *****************************************************************************
TEST(unaryPlus, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(2.2, 1.0, -5.2));
	myPoints.push_back(Vector3(1.0, -2.0, 1.7));
	Shape2d myShape(myPoints);

	myShape = +myShape;

	CHECK_DOUBLES_EQUAL(2.2, myShape[0].x, 0.0);
	CHECK_DOUBLES_EQUAL(1.0, myShape[0].y, 0.0);
	CHECK_DOUBLES_EQUAL(-5.2, myShape[0].z, 0.0);
	CHECK_DOUBLES_EQUAL(1.0, myShape[1].x, 0.0);
	CHECK_DOUBLES_EQUAL(-2.0, myShape[1].y, 0.0);
	CHECK_DOUBLES_EQUAL(1.7, myShape[1].z, 0.0);
}

TEST(unaryMinus, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(2.2, 1.0, -5.2));
	myPoints.push_back(Vector3(1.0, -2.0, 1.7));
	Shape2d myShape(myPoints);

	myShape = -myShape;

	CHECK_DOUBLES_EQUAL(-2.2, myShape[0].x, 0.0);
	CHECK_DOUBLES_EQUAL(-1.0, myShape[0].y, 0.0);
	CHECK_DOUBLES_EQUAL(5.2, myShape[0].z, 0.0);
	CHECK_DOUBLES_EQUAL(-1.0, myShape[1].x, 0.0);
	CHECK_DOUBLES_EQUAL(2.0, myShape[1].y, 0.0);
	CHECK_DOUBLES_EQUAL(-1.7, myShape[1].z, 0.0);
}

// *****************************************************************************
// Read-only indexing operation test
// *****************************************************************************
TEST(indexing, Shape2d)
{
	// Do nothing. Tested extensively in other tests.
}

// *****************************************************************************
// Scale and translate operation tests
// *****************************************************************************
TEST(scale, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(2.2, 1.0, -5.2));
	myPoints.push_back(Vector3(1.0, -2.0, 1.7));
	Shape2d myShape(myPoints);

	myShape.scale(2.0);

	CHECK_DOUBLES_EQUAL(4.4, myShape[0].x, 0.0);
	CHECK_DOUBLES_EQUAL(2.0, myShape[0].y, 0.0);
	CHECK_DOUBLES_EQUAL(-10.4, myShape[0].z, 0.0);
	CHECK_DOUBLES_EQUAL(2.0, myShape[1].x, 0.0);
	CHECK_DOUBLES_EQUAL(-4.0, myShape[1].y, 0.0);
	CHECK_DOUBLES_EQUAL(3.4, myShape[1].z, 0.0);
}

TEST(translate, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(2.2, 1.0, -5.2));
	myPoints.push_back(Vector3(1.0, -2.0, 1.7));
	Shape2d myShape(myPoints);

	// Define Vector3
	Vector3 myVector(3.0, -1.5, 2.0);

	myShape.translate(myVector);

	CHECK_DOUBLES_EQUAL(5.2, myShape[0].x, 0.0);
	CHECK_DOUBLES_EQUAL(-0.5, myShape[0].y, 0.0);
	CHECK_DOUBLES_EQUAL(-3.2, myShape[0].z, 0.0);
	CHECK_DOUBLES_EQUAL(4.0, myShape[1].x, 0.0);
	CHECK_DOUBLES_EQUAL(-3.5, myShape[1].y, 0.0);
	CHECK_DOUBLES_EQUAL(3.7, myShape[1].z, 0.0);
}

TEST(lerp, Shape2d)
{
	// Define shape1
	std::vector<Vector3> myPoints1;
	myPoints1.push_back(Vector3(2.0, 1.0, 0.0));
	myPoints1.push_back(Vector3(1.0, -2.0, 0.0));
	Shape2d myShape1(myPoints1);

	// Define shape2
	std::vector<Vector3> myPoints2;
	myPoints2.push_back(Vector3(0.0, 2.0, 2.0));
	Shape2d myShape2(myPoints2);

	// Different size, should return myShape1
	Shape2d lerpShape = Shape2d::lerp(myShape1, myShape2, 0.5);

	CHECK_DOUBLES_EQUAL(myShape1[0].x, lerpShape[0].x, TOL);
	CHECK_DOUBLES_EQUAL(myShape1[0].y, lerpShape[0].y, TOL);
	CHECK_DOUBLES_EQUAL(myShape1[0].z, lerpShape[0].z, TOL);
	CHECK_DOUBLES_EQUAL(myShape1[1].x, lerpShape[1].x, TOL);
	CHECK_DOUBLES_EQUAL(myShape1[1].y, lerpShape[1].y, TOL);
	CHECK_DOUBLES_EQUAL(myShape1[1].z, lerpShape[1].z, TOL);

	// Add point and try again
	myPoints2.push_back(Vector3(1.0, -2.0, 2.0));
	myShape2 = Shape2d(myPoints2);

	// Interpolate to first endpoint
	lerpShape = Shape2d::lerp(myShape1, myShape2, 0.0);

	CHECK_DOUBLES_EQUAL(myShape1[0].x, lerpShape[0].x, TOL);
	CHECK_DOUBLES_EQUAL(myShape1[0].y, lerpShape[0].y, TOL);
	CHECK_DOUBLES_EQUAL(myShape1[0].z, lerpShape[0].z, TOL);
	CHECK_DOUBLES_EQUAL(myShape1[1].x, lerpShape[1].x, TOL);
	CHECK_DOUBLES_EQUAL(myShape1[1].y, lerpShape[1].y, TOL);
	CHECK_DOUBLES_EQUAL(myShape1[1].z, lerpShape[1].z, TOL);

	// Interpolate to second endpoint
	lerpShape = Shape2d::lerp(myShape1, myShape2, 1.0);

	CHECK_DOUBLES_EQUAL(myShape2[0].x, lerpShape[0].x, TOL);
	CHECK_DOUBLES_EQUAL(myShape2[0].y, lerpShape[0].y, TOL);
	CHECK_DOUBLES_EQUAL(myShape2[0].z, lerpShape[0].z, TOL);
	CHECK_DOUBLES_EQUAL(myShape2[1].x, lerpShape[1].x, TOL);
	CHECK_DOUBLES_EQUAL(myShape2[1].y, lerpShape[1].y, TOL);
	CHECK_DOUBLES_EQUAL(myShape2[1].z, lerpShape[1].z, TOL);

	// Interpolate to halfway between endpoints
	lerpShape = Shape2d::lerp(myShape1, myShape2, 0.5);

	CHECK_DOUBLES_EQUAL(1.0, lerpShape[0].x, TOL);
	CHECK_DOUBLES_EQUAL(1.5, lerpShape[0].y, TOL);
	CHECK_DOUBLES_EQUAL(1.0, lerpShape[0].z, TOL);
	CHECK_DOUBLES_EQUAL(1.0, lerpShape[1].x, TOL);
	CHECK_DOUBLES_EQUAL(-2.0, lerpShape[1].y, TOL);
	CHECK_DOUBLES_EQUAL(1.0, lerpShape[1].z, TOL);
}

TEST(rotateAxisAngle, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(1.0, 1.0, 0.0));
	myPoints.push_back(Vector3(1.0, -1.0, 0.0));
	myPoints.push_back(Vector3(-1.0, -1.0, 0.0));
	myPoints.push_back(Vector3(-1.0, 1.0, 0.0));
	Shape2d myShape(myPoints);

	// Rotate 45 degrees around the z-aaxis
	Vector3 axis(0.0, 0.0, 1.0);
	double angle = 45.0 * DEG_TO_RAD;

	Shape2d rotShape = Shape2d::rotate(myShape, axis, angle);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[0].x, TOL);
	CHECK_DOUBLES_EQUAL(1.4142136, rotShape[0].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[0].z, TOL);
	CHECK_DOUBLES_EQUAL(1.4142136, rotShape[1].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[1].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[1].z, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[2].x, TOL);
	CHECK_DOUBLES_EQUAL(-1.4142136, rotShape[2].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[2].z, TOL);
	CHECK_DOUBLES_EQUAL(-1.4142136, rotShape[3].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[3].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[3].z, TOL);
}

// This test will rotate a 2 x 2 square inplane -45 degree about the point (-2,1,0)
TEST(rotateAxisAngleOrigin, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(-1.0, 2.0, 0.0));
	myPoints.push_back(Vector3(-1.0, 0.0, 0.0));
	myPoints.push_back(Vector3(-3.0, 0.0, 0.0));
	myPoints.push_back(Vector3(-3.0, 2.0, 0.0));
	Shape2d myShape(myPoints);

	// Rotate -45 degrees around the z-axis centered at (-2,1,0)
	Vector3 origin(-2.0, 1.0, 0.0);
	Vector3 axis(0.0, 0.0, 1.0);
	double angle = -45.0 * DEG_TO_RAD;

	Shape2d rotShape = Shape2d::rotate(myShape, axis, angle, origin);
	CHECK_DOUBLES_EQUAL(-0.5857864, rotShape[0].x, TOL);
	CHECK_DOUBLES_EQUAL(1.0000000, rotShape[0].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[0].z, TOL);
	CHECK_DOUBLES_EQUAL(-2.0000000, rotShape[1].x, TOL);
	CHECK_DOUBLES_EQUAL(-0.4142136, rotShape[1].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[1].z, TOL);
	CHECK_DOUBLES_EQUAL(-3.4142136, rotShape[2].x, TOL);
	CHECK_DOUBLES_EQUAL(1.0000000, rotShape[2].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[2].z, TOL);
	CHECK_DOUBLES_EQUAL(-2.0000000, rotShape[3].x, TOL);
	CHECK_DOUBLES_EQUAL(2.4142136, rotShape[3].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[3].z, TOL);
}

// This test will rotate a 2 x 2 square inplane -45 degree about the point (-2,1,0)
TEST(rotateSelf, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(-1.0, 2.0, 0.0));
	myPoints.push_back(Vector3(-1.0, 0.0, 0.0));
	myPoints.push_back(Vector3(-3.0, 0.0, 0.0));
	myPoints.push_back(Vector3(-3.0, 2.0, 0.0));
	Shape2d rotShape(myPoints);

	// Rotate -45 degrees around the z-axis centered at (-2,1,0)
	Vector3 origin(-2.0, 1.0, 0.0);
	Vector3 axis(0.0, 0.0, 1.0);
	double angle = -45.0 * DEG_TO_RAD;

	rotShape.rotate(axis, angle, origin);
	CHECK_DOUBLES_EQUAL(-0.5857864, rotShape[0].x, TOL);
	CHECK_DOUBLES_EQUAL(1.0000000, rotShape[0].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[0].z, TOL);
	CHECK_DOUBLES_EQUAL(-2.0000000, rotShape[1].x, TOL);
	CHECK_DOUBLES_EQUAL(-0.4142136, rotShape[1].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[1].z, TOL);
	CHECK_DOUBLES_EQUAL(-3.4142136, rotShape[2].x, TOL);
	CHECK_DOUBLES_EQUAL(1.0000000, rotShape[2].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[2].z, TOL);
	CHECK_DOUBLES_EQUAL(-2.0000000, rotShape[3].x, TOL);
	CHECK_DOUBLES_EQUAL(2.4142136, rotShape[3].y, TOL);
	CHECK_DOUBLES_EQUAL(0.0000000, rotShape[3].z, TOL);
}

// *****************************************************************************
// Non-member binary operator overloads
// *****************************************************************************
TEST(isEqual, Shape2d)
{
	// Define shape1
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(-1.0, 2.0, 0.0));
	myPoints.push_back(Vector3(-1.0, 0.0, 0.0));
	myPoints.push_back(Vector3(-3.0, 0.0, 0.0));
	myPoints.push_back(Vector3(-3.0, 2.0, 0.0));
	
	Shape2d myShape1(myPoints);

	// Define shape2
	Shape2d myShape2(myShape1);
	
	// Is myShape1 equal to itself?
	CHECK(myShape1 == myShape1);

	// Is myShape1 equal to myShape2?
	CHECK(myShape1 == myShape2);

	// Modify myShape2 and try again
	myPoints.push_back(Vector3(0.0, 0.0, 0.0));
	myShape2 = Shape2d(myPoints);

	CHECK(!(myShape1 == myShape2));
}

TEST(notIsEqual, Shape2d)
{
	// Define shape1
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(-1.0, 2.0, 0.0));
	myPoints.push_back(Vector3(-1.0, 0.0, 0.0));
	Shape2d myShape1(myPoints);

	// Define shape2
	myPoints.clear();
	myPoints.push_back(Vector3(-3.0, 0.0, 0.0));
	myPoints.push_back(Vector3(-3.0, 2.0, 0.0));
	Shape2d myShape2(myPoints);

	// Check that they are not equal
	CHECK(myShape1 != myShape2);
}

TEST(plus, Shape2d)
{
	// Define shape1
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(-1.0, 2.0, 3.0));
	myPoints.push_back(Vector3(-1.0, 1.0, 1.0));
	Shape2d myShape1(myPoints);

	// Define shape2
	myPoints.clear();
	myPoints.push_back(Vector3(-3.0, 0.0, 0.0));
	Shape2d myShape2(myPoints);

	// Not the same size - result should be Shape1
	Shape2d myShapeResult = myShape1 + myShape2;
	CHECK(myShapeResult == myShape1);

	// Add point to myShape2 and try again
	myPoints.push_back(Vector3(-5.0, 2.0, 0.0));
	myShape2 = Shape2d(myPoints);

	myShapeResult = myShape1 + myShape2;

	CHECK_DOUBLES_EQUAL(-4.0, myShapeResult[0].x, TOL);
	CHECK_DOUBLES_EQUAL(2.0, myShapeResult[0].y, TOL);
	CHECK_DOUBLES_EQUAL(3.0, myShapeResult[0].z, TOL);
	CHECK_DOUBLES_EQUAL(-6.0, myShapeResult[1].x, TOL);
	CHECK_DOUBLES_EQUAL(3.0, myShapeResult[1].y, TOL);
	CHECK_DOUBLES_EQUAL(1.0, myShapeResult[1].z, TOL);
}

TEST(minus, Shape2d)
{
	// Define shape1
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(-1.0, 2.0, 3.0));
	myPoints.push_back(Vector3(-1.0, 1.0, 1.0));
	Shape2d myShape1(myPoints);

	// Define shape2
	myPoints.clear();
	myPoints.push_back(Vector3(-3.0, 0.0, 0.0));
	Shape2d myShape2(myPoints);

	// Not the same size - result should be Shape1
	Shape2d myShapeResult = myShape1 - myShape2;
	CHECK(myShapeResult == myShape1);

	// Add point to myShape2 and try again
	myPoints.push_back(Vector3(-5.0, 2.0, 0.0));
	myShape2 = Shape2d(myPoints);

	myShapeResult = myShape1 - myShape2;

	CHECK_DOUBLES_EQUAL(2.0, myShapeResult[0].x, TOL);
	CHECK_DOUBLES_EQUAL(2.0, myShapeResult[0].y, TOL);
	CHECK_DOUBLES_EQUAL(3.0, myShapeResult[0].z, TOL);
	CHECK_DOUBLES_EQUAL(4.0, myShapeResult[1].x, TOL);
	CHECK_DOUBLES_EQUAL(-1.0, myShapeResult[1].y, TOL);
	CHECK_DOUBLES_EQUAL(1.0, myShapeResult[1].z, TOL);
}

TEST(times1, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(-1.0, 2.0, 3.0));
	myPoints.push_back(Vector3(-1.0, 1.0, 1.0));
	Shape2d myShape(myPoints);

	// Define scalar
	double scalar = 2.0;

	// Multiply together
	Shape2d myShapeResult = scalar * myShape;

	CHECK_DOUBLES_EQUAL(-2.0, myShapeResult[0].x, TOL);
	CHECK_DOUBLES_EQUAL(4.0, myShapeResult[0].y, TOL);
	CHECK_DOUBLES_EQUAL(6.0, myShapeResult[0].z, TOL);
	CHECK_DOUBLES_EQUAL(-2.0, myShapeResult[1].x, TOL);
	CHECK_DOUBLES_EQUAL(2.0, myShapeResult[1].y, TOL);
	CHECK_DOUBLES_EQUAL(2.0, myShapeResult[1].z, TOL);
}

TEST(times2, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(-1.0, 2.0, 3.0));
	myPoints.push_back(Vector3(-1.0, 1.0, 1.0));
	Shape2d myShape(myPoints);

	// Define scalar
	double scalar = 2.0;

	// Multiply together
	Shape2d myShapeResult = myShape * scalar;

	CHECK_DOUBLES_EQUAL(-2.0, myShapeResult[0].x, TOL);
	CHECK_DOUBLES_EQUAL(4.0, myShapeResult[0].y, TOL);
	CHECK_DOUBLES_EQUAL(6.0, myShapeResult[0].z, TOL);
	CHECK_DOUBLES_EQUAL(-2.0, myShapeResult[1].x, TOL);
	CHECK_DOUBLES_EQUAL(2.0, myShapeResult[1].y, TOL);
	CHECK_DOUBLES_EQUAL(2.0, myShapeResult[1].z, TOL);
}

TEST(divide, Shape2d)
{
	// Define shape
	std::vector<Vector3> myPoints;
	myPoints.push_back(Vector3(-1.0, 2.0, 3.0));
	myPoints.push_back(Vector3(-1.0, 1.0, 1.0));
	Shape2d myShape(myPoints);

	// Define scalar
	double scalar = 2.0;

	// Divide
	Shape2d myShapeResult = myShape / scalar;

	CHECK_DOUBLES_EQUAL(-0.5, myShapeResult[0].x, TOL);
	CHECK_DOUBLES_EQUAL(1.0, myShapeResult[0].y, TOL);
	CHECK_DOUBLES_EQUAL(1.5, myShapeResult[0].z, TOL);
	CHECK_DOUBLES_EQUAL(-0.5, myShapeResult[1].x, TOL);
	CHECK_DOUBLES_EQUAL(0.5, myShapeResult[1].y, TOL);
	CHECK_DOUBLES_EQUAL(0.5, myShapeResult[1].z, TOL);
}

