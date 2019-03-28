// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

// Contains methods for Airfoil creation

#pragma once

#include <vector>

#include "Shape2d.h"

class Airfoil :	public Shape2d
{
public:
	// Default Constructor
	Airfoil() = default;

	// Construct from Vector3 points
	Airfoil(const std::vector<Vector3>& points);

	// Copy constructor and assignment operator
	Airfoil(const Airfoil& src) = default;
	Airfoil& operator=(const Airfoil& rhs) = default;

	// Destructor
	~Airfoil() = default;

	// Linear interpolation method
	static Airfoil lerp(const Airfoil& airfoil1, const Airfoil& airfoil2, double t);

	// Static functions
	static Airfoil makeNACA4(int n, double t, double m, double p, bool closeTE = true);
	static Airfoil readSeligFormat(const std::string& file, int n);

private:
	// Redistribute airfoil to n cosine-spaced points using linear interpolation
	static void redistributeAirfoil(int n, std::vector<Vector3>& points);

	// Cosine rule for ordinate spacing
	static double cosineSpacing(int n, int i);
};

