// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#define _USE_MATH_DEFINES

#include "Vector3.h"
#include "TestHarness.h"

// Global tolerance value
const static double TOL = 1.0e-6;

// Degrees to Radians conversion factor
const static double DEG_TO_RAD = M_PI / 180.0;

// *****************************************************************************
// Constructor Tests
// *****************************************************************************
TEST(defaultConstructor, Vector3)
{
	Vector3 myVector;
	CHECK_DOUBLES_EQUAL(0.0, myVector.x, 0.0);
	CHECK_DOUBLES_EQUAL(0.0, myVector.y, 0.0);
	CHECK_DOUBLES_EQUAL(0.0, myVector.z, 0.0);
}

TEST(valueConstructor, Vector3)
{
	Vector3 myVector(3.2, -4.7, 5.3);

	CHECK_DOUBLES_EQUAL(3.2, myVector.x, 0.0);
	CHECK_DOUBLES_EQUAL(-4.7, myVector.y, 0.0);
	CHECK_DOUBLES_EQUAL(5.3, myVector.z, 0.0);
}

TEST(copyConstructor, Vector3)
{
	Vector3 myVector1(3.2, -4.7, 5.3);
	Vector3 myVector2(myVector1);

	CHECK_DOUBLES_EQUAL(myVector1.x, myVector2.x, 0.0);
	CHECK_DOUBLES_EQUAL(myVector1.y, myVector2.y, 0.0);
	CHECK_DOUBLES_EQUAL(myVector1.z, myVector2.z, 0.0);
}

// *****************************************************************************
// Assignment test
// *****************************************************************************
TEST(assignment, Vector3)
{
	Vector3 myVector1(3.2, -4.7, 5.3);
	Vector3 myVector2(-2.3, 6.1, 8.3);

	myVector2 = myVector1;

	CHECK_DOUBLES_EQUAL(myVector1.x, myVector2.x, 0.0);
	CHECK_DOUBLES_EQUAL(myVector1.y, myVector2.y, 0.0);
	CHECK_DOUBLES_EQUAL(myVector1.z, myVector2.z, 0.0);
}

// *****************************************************************************
// Compound operator tests
// *****************************************************************************
TEST(plusEquals, Vector3)
{
	Vector3 myVector1(3.2, -4.7, 5.3);
	Vector3 myVector2(-2.3, 6.1, 8.3);
	
	myVector1 += myVector2;

	CHECK_DOUBLES_EQUAL(0.9, myVector1.x, TOL);
	CHECK_DOUBLES_EQUAL(1.4, myVector1.y, TOL);
	CHECK_DOUBLES_EQUAL(13.6, myVector1.z, TOL);
}

TEST(minusEquals, Vector3)
{
	Vector3 myVector1(3.2, -4.7, 5.3);
	Vector3 myVector2(-2.3, 6.1, 8.3);

	myVector1 -= myVector2;

	CHECK_DOUBLES_EQUAL(5.5, myVector1.x, TOL);
	CHECK_DOUBLES_EQUAL(-10.8, myVector1.y, TOL);
	CHECK_DOUBLES_EQUAL(-3.0, myVector1.z, TOL);
}

TEST(timesEquals, Vector3)
{
	Vector3 myVector(3.2, -4.7, 5.3);
	double scalar = 2.5;

	myVector *= scalar;

	CHECK_DOUBLES_EQUAL(8.0, myVector.x, TOL);
	CHECK_DOUBLES_EQUAL(-11.75, myVector.y, TOL);
	CHECK_DOUBLES_EQUAL(13.25, myVector.z, TOL);
}

TEST(divideEquals, Vector3)
{
	Vector3 myVector(3.2, -4.7, 5.3);
	double scalar = 2.5;

	myVector /= scalar;

	CHECK_DOUBLES_EQUAL(1.28, myVector.x, TOL);
	CHECK_DOUBLES_EQUAL(-1.88, myVector.y, TOL);
	CHECK_DOUBLES_EQUAL(2.12, myVector.z, TOL);
}

// *****************************************************************************
// Unary operator tests
// *****************************************************************************
TEST(unaryPlus, Vector3)
{
	Vector3 myVector(3.2, -4.7, 5.3);

	myVector = +myVector;
	
	CHECK_DOUBLES_EQUAL(3.2, myVector.x, TOL);
	CHECK_DOUBLES_EQUAL(-4.7, myVector.y, TOL);
	CHECK_DOUBLES_EQUAL(5.3, myVector.z, TOL);
}

TEST(unaryMinus, Vector3)
{
	Vector3 myVector(3.2, -4.7, 5.3);

	myVector = -myVector;

	CHECK_DOUBLES_EQUAL(-3.2, myVector.x, TOL);
	CHECK_DOUBLES_EQUAL(4.7, myVector.y, TOL);
	CHECK_DOUBLES_EQUAL(-5.3, myVector.z, TOL);
}

// *****************************************************************************
// Vector operation tests
// *****************************************************************************
TEST(lengthSquared, Vector3)
{
	Vector3 myVector(1.1, 2.2, 3.3);

	CHECK_DOUBLES_EQUAL(16.94, myVector.lengthSquared(), TOL);
}

TEST(length, Vector3)
{
	Vector3 myVector(1.0, 2.0, 3.0);

	CHECK_DOUBLES_EQUAL(3.7416574, myVector.length(), TOL);
}

TEST(dot, Vector3)
{
	Vector3 myVector1(1.0, 2.0, 3.0);
	Vector3 myVector2(4.0, -5.0, 6.0);

	double dotProd = myVector1.dot(myVector2);

	CHECK_DOUBLES_EQUAL(12.0, dotProd, TOL);
}

TEST(cross, Vector3)
{
	Vector3 myVector1(3.0, -3.0, 1.0);
	Vector3 myVector2(4.0, 9.0, 2.0);

	Vector3 crossProd = myVector1.cross(myVector2);

	CHECK_DOUBLES_EQUAL(-15.0, crossProd.x, TOL);
	CHECK_DOUBLES_EQUAL(-2.0, crossProd.y, TOL);
	CHECK_DOUBLES_EQUAL(39.0, crossProd.z, TOL);
}

TEST(normalize, Vector3)
{
	Vector3 myVector;

	// Check normalizing zero vector
	myVector.normalize();

	CHECK_DOUBLES_EQUAL(0.0, myVector.x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, myVector.y, TOL);
	CHECK_DOUBLES_EQUAL(0.0, myVector.z, TOL);

	// Check normalizing non-zero vector
	myVector.x = 1.0;
	myVector.y = 2.0;
	myVector.z = 3.0;

	myVector.normalize();

	CHECK_DOUBLES_EQUAL(0.2672612, myVector.x, TOL);
	CHECK_DOUBLES_EQUAL(0.5345225, myVector.y, TOL);
	CHECK_DOUBLES_EQUAL(0.8017837, myVector.z, TOL);

	// Final check, length should be 1.0
	CHECK_DOUBLES_EQUAL(1.0, myVector.length(), TOL);
}

TEST(lerp, Vector3)
{
	Vector3 myVector1(1.0, 2.0, 3.0);
	Vector3 myVector2(5.0, -8.0, 15.0);

	// Interpolate to first endpoint
	Vector3 lerpVec = Vector3::lerp(myVector1, myVector2, 0.0);
	
	CHECK_DOUBLES_EQUAL(myVector1.x, lerpVec.x, TOL);
	CHECK_DOUBLES_EQUAL(myVector1.y, lerpVec.y, TOL);
	CHECK_DOUBLES_EQUAL(myVector1.z, lerpVec.z, TOL);

	// Interpolate to second endpoint
	lerpVec = Vector3::lerp(myVector1, myVector2, 1.0);

	CHECK_DOUBLES_EQUAL(myVector2.x, lerpVec.x, TOL);
	CHECK_DOUBLES_EQUAL(myVector2.y, lerpVec.y, TOL);
	CHECK_DOUBLES_EQUAL(myVector2.z, lerpVec.z, TOL);

	// Interpolate to halfway between endpoints
	lerpVec = Vector3::lerp(myVector1, myVector2, 0.5);

	CHECK_DOUBLES_EQUAL(3.0, lerpVec.x, TOL);
	CHECK_DOUBLES_EQUAL(-3.0, lerpVec.y, TOL);
	CHECK_DOUBLES_EQUAL(9.0, lerpVec.z, TOL);
}

TEST(rotateAxisAngle, Vector3)
{
	Vector3 vec(1.0, 2.0, 3.0);

	// First rotate around x-axis by 30.0 deg
	Vector3 axis(1.0, 0.0, 0.0);
	double angle = 30.0 * DEG_TO_RAD;

	Vector3 rotVec = Vector3::rotate(vec, axis, angle);
	CHECK_DOUBLES_EQUAL(1.0000000, rotVec.x, TOL);
	CHECK_DOUBLES_EQUAL(0.2320508, rotVec.y, TOL);
	CHECK_DOUBLES_EQUAL(3.5980762, rotVec.z, TOL);

	// Next, rotate around new y-axis by -95.0 deg
	axis = Vector3(0.0, 1.0, 0.0);
	angle = -95.0 * DEG_TO_RAD;

	rotVec = Vector3::rotate(rotVec, axis, angle);
	CHECK_DOUBLES_EQUAL(-3.6715402, rotVec.x, TOL);
	CHECK_DOUBLES_EQUAL(0.2320508, rotVec.y, TOL);
	CHECK_DOUBLES_EQUAL(0.6826017, rotVec.z, TOL);

	// Next, rotate around new z-axis by 90.0 deg
	axis = Vector3(0.0, 0.0, 1.0);
	angle = 90.0 * DEG_TO_RAD;

	rotVec = Vector3::rotate(rotVec, axis, angle);
	CHECK_DOUBLES_EQUAL(-0.2320508, rotVec.x, TOL);
	CHECK_DOUBLES_EQUAL(-3.6715402, rotVec.y, TOL);
	CHECK_DOUBLES_EQUAL(0.6826017, rotVec.z, TOL);

	// Finally, do it again as one big rotation
	axis = Vector3(0.663578618412749, -0.401957358842021, 0.630946668790773);
	angle = 141.886370 * DEG_TO_RAD;

	rotVec = Vector3::rotate(vec, axis, angle);
	CHECK_DOUBLES_EQUAL(-0.2320508, rotVec.x, TOL);
	CHECK_DOUBLES_EQUAL(-3.6715402, rotVec.y, TOL);
	CHECK_DOUBLES_EQUAL(0.6826017, rotVec.z, TOL);
}

TEST(rotateSelf, Vector3)
{
	Vector3 rotVec(1.0, 2.0, 3.0);

	// First rotate around x-axis by 30.0 deg
	Vector3 axis(1.0, 0.0, 0.0);
	double angle = 30.0 * DEG_TO_RAD;

	rotVec.rotate(axis, angle);
	CHECK_DOUBLES_EQUAL(1.0000000, rotVec.x, TOL);
	CHECK_DOUBLES_EQUAL(0.2320508, rotVec.y, TOL);
	CHECK_DOUBLES_EQUAL(3.5980762, rotVec.z, TOL);

	// Next, rotate around new y-axis by -95.0 deg
	axis = Vector3(0.0, 1.0, 0.0);
	angle = -95.0 * DEG_TO_RAD;

	rotVec.rotate(axis, angle);
	CHECK_DOUBLES_EQUAL(-3.6715402, rotVec.x, TOL);
	CHECK_DOUBLES_EQUAL(0.2320508, rotVec.y, TOL);
	CHECK_DOUBLES_EQUAL(0.6826017, rotVec.z, TOL);

	// Next, rotate around new z-axis by 90.0 deg
	axis = Vector3(0.0, 0.0, 1.0);
	angle = 90.0 * DEG_TO_RAD;

	rotVec.rotate(axis, angle);
	CHECK_DOUBLES_EQUAL(-0.2320508, rotVec.x, TOL);
	CHECK_DOUBLES_EQUAL(-3.6715402, rotVec.y, TOL);
	CHECK_DOUBLES_EQUAL(0.6826017, rotVec.z, TOL);

	// Finally, do it again as one big rotation
	axis = Vector3(0.663578618412749, -0.401957358842021, 0.630946668790773);
	angle = 141.886370 * DEG_TO_RAD;

	rotVec = Vector3(1.0, 2.0, 3.0);
	rotVec.rotate(axis, angle);
	CHECK_DOUBLES_EQUAL(-0.2320508, rotVec.x, TOL);
	CHECK_DOUBLES_EQUAL(-3.6715402, rotVec.y, TOL);
	CHECK_DOUBLES_EQUAL(0.6826017, rotVec.z, TOL);
}

// *****************************************************************************
// Non-member binary operator overloads
// *****************************************************************************
TEST(isEqual, Vector3)
{
	Vector3 myVector1(1.1, 2.2, 3.3);
	Vector3 myVector2(1.1, 2.2, 3.3);

	// Is myVector1 equal to itself?
	CHECK(myVector1 == myVector1);

	// Is myVector1 equal to myVector2?
	CHECK(myVector1 == myVector2);
}

TEST(notIsEqual, Vector3)
{
	Vector3 myVector1(1.1, 2.2, 3.3);
	Vector3 myVector2(2.2, 4.4, 6.6);

	// Is myVector1 not equal to itself?
	CHECK(!(myVector1 != myVector1));

	// Is myVector1 not equal to myVector2?
	CHECK(myVector1 != myVector2);
}

TEST(plus, Vector3)
{
	Vector3 myVector1(3.2, -4.7, 5.3);
	Vector3 myVector2(-2.3, 6.1, 8.3);

	Vector3 myVector3 = myVector1 + myVector2;

	CHECK_DOUBLES_EQUAL(0.9, myVector3.x, TOL);
	CHECK_DOUBLES_EQUAL(1.4, myVector3.y, TOL);
	CHECK_DOUBLES_EQUAL(13.6, myVector3.z, TOL);
}

TEST(minus, Vector3)
{
	Vector3 myVector1(3.2, -4.7, 5.3);
	Vector3 myVector2(-2.3, 6.1, 8.3);

	Vector3 myVector3 = myVector1 - myVector2;

	CHECK_DOUBLES_EQUAL(5.5, myVector3.x, TOL);
	CHECK_DOUBLES_EQUAL(-10.8, myVector3.y, TOL);
	CHECK_DOUBLES_EQUAL(-3.0, myVector3.z, TOL);
}

TEST(times1, Vector3)
{
	Vector3 myVector1(3.2, -4.7, 5.3);
	double scalar = 2.5;

	Vector3 myVector2 = scalar*myVector1;

	CHECK_DOUBLES_EQUAL(8.0, myVector2.x, TOL);
	CHECK_DOUBLES_EQUAL(-11.75, myVector2.y, TOL);
	CHECK_DOUBLES_EQUAL(13.25, myVector2.z, TOL);
}

TEST(times2, Vector3)
{
	Vector3 myVector1(3.2, -4.7, 5.3);
	double scalar = 2.5;

	Vector3 myVector2 = myVector1*scalar;

	CHECK_DOUBLES_EQUAL(8.0, myVector2.x, TOL);
	CHECK_DOUBLES_EQUAL(-11.75, myVector2.y, TOL);
	CHECK_DOUBLES_EQUAL(13.25, myVector2.z, TOL);
}

TEST(divide, Vector3)
{
	Vector3 myVector1(3.2, -4.7, 5.3);
	double scalar = 2.5;

	Vector3 myVector2 = myVector1/scalar;

	CHECK_DOUBLES_EQUAL(1.28, myVector2.x, TOL);
	CHECK_DOUBLES_EQUAL(-1.88, myVector2.y, TOL);
	CHECK_DOUBLES_EQUAL(2.12, myVector2.z, TOL);
}
