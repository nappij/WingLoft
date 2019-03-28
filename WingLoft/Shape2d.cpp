// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "Shape2d.h"

// *****************************************************************************
// Constructor
// *****************************************************************************
Shape2d::Shape2d(const std::vector<Vector3>& points)
	: points(points)
{
}

// *****************************************************************************
// Compound operators
// *****************************************************************************

// Add two Shape2ds in place
Shape2d& Shape2d::operator+=(const Shape2d& rhs)
{
	// Perform action only if both shapes have the same number of points
	if (this->points.size() == rhs.points.size())
	{
		for (size_t i = 0; i < this->points.size(); ++i)
			points[i] += rhs[i];
	}
	return *this;
}

// Add Shape2d and Vector3 in place
Shape2d& Shape2d::operator+=(const Vector3& rhs)
{
	for (auto& point : points)
		point += rhs;
	return *this;
}

// Subtract two Shape2ds in place
Shape2d& Shape2d::operator-=(const Shape2d& rhs)
{
	// Perform action only if both shapes have the same number of points
	if (this->points.size() == rhs.points.size())
	{
		for (size_t i = 0; i < this->points.size(); ++i)
			points[i] -= rhs[i];
	}
	return *this;
}

// Subtract Shape2d and Vector3 in place
Shape2d& Shape2d::operator-=(const Vector3& rhs)
{
	for (auto& point : points)
		point -= rhs;
	return *this;
}

// Multiply Shape2d by a scalar in place
Shape2d& Shape2d::operator*=(double s)
{
	for (auto& point : points)
		point *= s;
	return *this;
}

// Divide Shape2d by a scalar in place
Shape2d& Shape2d::operator/=(double s)
{
	for (auto& point : points)
		point /= s;
	return *this;
}

// *****************************************************************************
// Unary operators
// *****************************************************************************

// Return Shape2d
Shape2d Shape2d::operator+() const
{
	return *this;
}

// Return negation of Shape2d
Shape2d Shape2d::operator-() const
{
	std::vector<Vector3> newPoints;
	for (auto& point : points)
		newPoints.push_back(-point);
	return Shape2d(newPoints);
}

// *****************************************************************************
// Read-only indexing operator
// *****************************************************************************
const Vector3& Shape2d::operator[](size_t i) const
{
	return points[i];
}

// *****************************************************************************
// Shape2d transformation methods
// *****************************************************************************

// Scale Shape2d by scalar s
void Shape2d::scale(double s)
{
	*this *= s;
}

// Translate Shape2d by Vector3
void Shape2d::translate(const Vector3& t)
{
	*this += t;
}

// Linearly interpolate between two Shape2d's
Shape2d Shape2d::lerp(const Shape2d& shape1, const Shape2d& shape2, double t)
{
	// Perform action only if both shapes have the same number of points
	if (shape1.points.size() == shape2.points.size())
	{
		std::vector<Vector3> newPoints;
		for (size_t i = 0; i < shape1.points.size(); ++i)
			newPoints.push_back(Vector3::lerp(shape1[i], shape2[i], t));
		return Shape2d(newPoints);
	}
	return shape1;
}

// Rotate Shape2d about an axis through an origin by angle radians, return new Shape2d
Shape2d Shape2d::rotate(const Shape2d& shape, const Vector3& axis, double angle, const Vector3& origin)
{
	// Copy shape into newShape
	Shape2d newShape(shape);

	// Translate to origin
	newShape -= origin;

	// Rotate around axis by angle
	std::vector<Vector3> newPoints;
	for (size_t i = 0; i < shape.points.size(); ++i)
		newPoints.push_back(Vector3::rotate(newShape[i], axis, angle));
	newShape = Shape2d(newPoints);

	// Translate back to original location
	newShape += origin;

	return newShape;
}

// Rotate this Shape2d about an axis through an origin by angle radians
void Shape2d::rotate(const Vector3& axis, double angle, const Vector3& origin)
{
	Shape2d rotShape = *this;
	*this = Shape2d::rotate(rotShape, axis, angle, origin);
}

// *****************************************************************************
// Non-member binary operator overloads
// *****************************************************************************

// Check for equality between two Shape2d's
bool operator==(const Shape2d& shape1, const Shape2d& shape2)
{
	if (shape1.getPoints().size() != shape2.getPoints().size())
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < shape1.getPoints().size(); ++i)
			if (shape1[i] != shape2[i])	return false;
	}
	return true;
}

// Check for inequality between two Shape2d's
bool operator!=(const Shape2d& shape1, const Shape2d& shape2)
{
	return !(shape1 == shape2);
}

// Add two Shape2d's
Shape2d operator+(const Shape2d& shape1, const Shape2d& shape2)
{
	Shape2d result = shape1;
	return (result += shape2);
}

// Subtract two Shape2d's
Shape2d operator-(const Shape2d& shape1, const Shape2d& shape2)
{
	Shape2d result = shape1;
	return (result -= shape2);
}

// Multiply scalar by Shape2d
Shape2d operator*(double s, const Shape2d& shape)
{
	Shape2d result = shape;
	return (result *= s);
}

// Multiply Shape2d by scalar
Shape2d operator*(const Shape2d& shape, double s)
{
	return (s*shape);
}

// Divide Shape2d by scalar
Shape2d operator/(const Shape2d& shape, double s)
{
	Shape2d result = shape;
	return (result /= s);
}

// Send Shape2d to output stream
std::ostream& operator<<(std::ostream& os, const Shape2d& shape)
{
	for (size_t i = 0; i < shape.getPoints().size(); ++i)
		os << shape[i] << std::endl;
	return os;
}
