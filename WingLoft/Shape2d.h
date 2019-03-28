// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

// Contains a vector of points representing a 2D planar shape. This shape has various geometric transformation
// methods useful for lofting.

#pragma once

#include <vector>

#include "Vector3.h"

class Shape2d
{
public:
	// Constructors
	Shape2d() = default;
	Shape2d(const std::vector<Vector3>& points);
	
	// Copy constructor and assignment operator
	Shape2d(const Shape2d& src) = default;
	Shape2d& operator=(const Shape2d& rhs) = default;

	// Destructor
	virtual ~Shape2d() = default;

	// Compound operators
	Shape2d& operator+=(const Shape2d& rhs);
	Shape2d& operator+=(const Vector3& rhs);
	Shape2d& operator-=(const Shape2d& rhs);
	Shape2d& operator-=(const Vector3& rhs);
	Shape2d& operator*=(double s);
	Shape2d& operator/=(double s);

	// Unary operators
	Shape2d operator+() const;
	Shape2d operator-() const;

	// Read-only indexing operator
	const Vector3& operator[](size_t i) const;

	// Shape2d transformation methods
	void scale(double s);					// Scale Shape2d
	void translate(const Vector3& t);		// Translate Shape2d
	
	// Linear interpolation method
	static Shape2d lerp(const Shape2d& shape1, const Shape2d& shape2, double t);

	// Rotate methods
	static Shape2d rotate(const Shape2d& shape, const Vector3& axis, double angle, const Vector3& origin = Vector3(0.0, 0.0, 0.0));
	void rotate(const Vector3& axis, double angle, const Vector3& origin = Vector3(0.0, 0.0, 0.0));

	// Get read-only access to points
	const std::vector<Vector3> getPoints() const { return points; }

private:
	std::vector<Vector3> points;
};

// Non-member binary operator overloads
bool operator==(const Shape2d& shape1, const Shape2d& shape2);
bool operator!=(const Shape2d& shape1, const Shape2d& shape2);
Shape2d operator+(const Shape2d& shape1, const Shape2d& shape2);
Shape2d operator-(const Shape2d& shape1, const Shape2d& shape2);
Shape2d operator*(double s, const Shape2d& shape);
Shape2d operator*(const Shape2d& shape, double s);
Shape2d operator/(const Shape2d& shape, double s);
std::ostream& operator<<(std::ostream& os, const Shape2d& shape);