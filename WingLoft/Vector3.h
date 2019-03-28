// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

// Represents a 3D Vector or 3D Point (depending on usage context) with various geometric
// transformation methods useful for lofting.

#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

class Vector3
{
public:
	double x;		// x-coordinate of point
	double y;		// y-coordinate of point
	double z;		// z-coordinate of point

	// Constructors
	Vector3();
	Vector3(double x, double y, double z);
	
	// Copy constructor and assignment operator
	Vector3(const Vector3& src) = default;
	Vector3& operator=(const Vector3& rhs) = default;

	// Destructor
	~Vector3() = default;

	// Compound operators
	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3& operator*=(double s);
	Vector3& operator/=(double s);

	// Unary operators
	Vector3 operator+() const;
	Vector3 operator-() const;

	// Vector operations
	double lengthSquared() const;
	double length() const;

	double dot(const Vector3& rhs) const;
	Vector3 cross(const Vector3& rhs) const;

	void normalize();
	
	static Vector3 lerp(const Vector3& vec1, const Vector3& vec2, double t);
	
	static Vector3 rotate(const Vector3& vec, const Vector3& axis, double angle);
	void rotate(const Vector3& axis, double angle);
};

// Non-member binary operator overloads
bool operator==(const Vector3& vec1, const Vector3& vec2);
bool operator!=(const Vector3& vec1, const Vector3& vec2);
Vector3 operator+(const Vector3& vec1, const Vector3& vec2);
Vector3 operator-(const Vector3& vec1, const Vector3& vec2);
Vector3 operator*(double s, const Vector3& vec);
Vector3 operator*(const Vector3& vec, double s);
Vector3 operator/(const Vector3& vec, double s);
std::ostream& operator<<(std::ostream& os, const Vector3& vec);