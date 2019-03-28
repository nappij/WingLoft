// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "Vector3.h"

// *****************************************************************************
// Constructors
// *****************************************************************************
Vector3::Vector3()
	: Vector3(0.0, 0.0, 0.0)
{
}

Vector3::Vector3(double x, double y, double z)
	: x(x), y(y), z(z)
{
}

// *****************************************************************************
// Compound operators
// *****************************************************************************

// Add two Vector3s in place
inline Vector3& Vector3::operator+=(const Vector3& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

// Subtract two Vector3s in place
inline Vector3& Vector3::operator-=(const Vector3& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

// Multiply Vector3 by a scalar in place
inline Vector3& Vector3::operator*=(double s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

// Divide Vector3 by a scalar in place
inline Vector3& Vector3::operator/=(double s)
{
	assert(s != 0.0);
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

// *****************************************************************************
// Unary operators
// *****************************************************************************

// Return Vector3
Vector3 Vector3::operator+() const
{
	return *this;
}

// Return negation of Vector3
Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

// *****************************************************************************
// Vector operations
// *****************************************************************************

// Return squared length of Vector3
double Vector3::lengthSquared() const
{
	return (x*x + y*y + z*z);
}

// Return length of Vector3
double Vector3::length() const
{
	return sqrt(lengthSquared());
}

// Return dot product of Vector3
double Vector3::dot(const Vector3& rhs) const
{
	return (x*rhs.x + y*rhs.y + z*rhs.z);
}

// Return cross product of Vector3
Vector3 Vector3::cross(const Vector3& rhs) const
{
	return Vector3(y*rhs.z - z*rhs.y,
		           z*rhs.x - x*rhs.z,
		           x*rhs.y - y*rhs.x);
}

// Normalze Vector3
void Vector3::normalize()
{
	// The if check allows calling normalize() on a zero vector.
	if (lengthSquared() > 0.0)
	{
		double vecMag = length();
		x /= vecMag;
		y /= vecMag;
		z /= vecMag;
	}
}

// Linearly interpolate between two Vector3's
// Source: https://en.wikipedia.org/wiki/Linear_interpolation
Vector3 Vector3::lerp(const Vector3& vec1, const Vector3&  vec2, double t)
{
	// Check for out of range parameter, and return end points if so
	if (t <= 0.0) return vec1;
	if (t >= 1.0) return vec2;

	// General case
	return ((1.0 - t)*vec1 + t*vec2);
}

// Rotate Vector3 about an axis by angle radians, return new Vector3
// Source: https://en.wikipedia.org/wiki/Axis%E2%80%93angle_representation#Rotating_a_vector
Vector3 Vector3::rotate(const Vector3& vec, const Vector3& axis, double angle)
{
	// On input it is assumed:
	// 1.) Axis is through the origin
	// 2.) Axis is a unit vector, i.e. ||axis|| = 1.0
	// 3.) Angle is radians

	// Cosine and sine of theta
	double cTheta = cos(angle);
	double sTheta = sin(angle);

	// Compute rotation of Vector3 and return
	Vector3 vecRot = cTheta*vec + sTheta*(axis.cross(vec)) + (1.0 - cTheta)*axis.dot(vec)*axis;
	return vecRot;
}

// Rotate Vector3 about an axis by angle radians
void Vector3::rotate(const Vector3& axis, double angle)
{
	Vector3 rotVec = *this;
	*this = Vector3::rotate(rotVec, axis, angle);
}

// *****************************************************************************
// Non-member binary operator overloads
// *****************************************************************************

// Check for equality between two Vector3's
bool operator==(const Vector3& vec1, const Vector3& vec2)
{
	return (vec1.x == vec2.x
		&& vec1.y == vec2.y 
		&& vec1.z == vec2.z);
}

// Check for inequality between two Vector3's
bool operator!=(const Vector3& vec1, const Vector3& vec2)
{
	return !(vec1 == vec2);
}

// Add two Vector3's
Vector3 operator+(const Vector3& vec1, const Vector3& vec2)
{
	Vector3 result = vec1;
	return (result += vec2);
}

// Subtract two Vector3's
Vector3 operator-(const Vector3& vec1, const Vector3& vec2)
{
	Vector3 result = vec1;
	return (result -= vec2);
}

// Multiply scalar by Vector3
Vector3 operator*(double s, const Vector3& vec)
{
	Vector3 result = vec;	
	return (result *= s);
}

// Multiply Vector3 by scalar
Vector3 operator*(const Vector3& vec, double s)
{
	return (s*vec);
}

// Divide Vector3 by scalar
Vector3 operator/(const Vector3& vec, double s)
{
	Vector3 result = vec;
	return (result /= s);
}

// Send Vector3 to output stream
std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
	os << vec.x << " " << vec.y << " " << vec.z;
	return os;
}
