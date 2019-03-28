// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#define _USE_MATH_DEFINES

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Airfoil.h"

// *****************************************************************************
// Private constructor
// *****************************************************************************
Airfoil::Airfoil(const std::vector<Vector3>& points)
	: Shape2d(points)
{
}

// *****************************************************************************
// Static methods for Airfoil creation
// *****************************************************************************

// Linear interpolation of two airfoils
Airfoil Airfoil::lerp(const Airfoil & airfoil1, const Airfoil & airfoil2, double t)
{
	// Perform action only if both airfoil have the same number of points
	if (airfoil1.getPoints().size() == airfoil2.getPoints().size())
	{
		std::vector<Vector3> newPoints;
		for (size_t i = 0; i < airfoil1.getPoints().size(); ++i)
			newPoints.push_back(Vector3::lerp(airfoil1[i], airfoil2[i], t));
		return Airfoil(newPoints);
	}
	return airfoil1;
}

// Create a NACA 4-Series airfoil - will get redistributed to n linearly spaced ordinates
// Source: https://en.wikipedia.org/wiki/NACA_airfoil#Four-digit_series
Airfoil Airfoil::makeNACA4(int n, double t, double m, double p, bool closeTE)
{
	// Argument description:
	// n is the number of cosine rule spaced chord stations to compute airfoil, the airfoil will be 2*n - 1 points.
	// t is the maximum thickness of the airfoil (the last two digits, divided by 100)
	// m is the maximum camber as a percentage of the chord (the first digit, divided by 100)
	// p is the distance of maximum camber from the leading edge (the second digit, divided by 10)
	// closeTE- true to close the trailing edge, false for finite thickness

	// Create the original airfoil with a rich number of points. Later we'll redistribute it to the n
	// chord stations asked for.
	const int nRich = 200;

	// Vector of upper and lower airfoil points
	std::vector<Vector3> upperPoints;
	std::vector<Vector3> lowerPoints;

	// Determine last coefficient in thickness formula
	double k5;
	if (closeTE)
		k5 = 0.1036;
	else
		k5 = 0.1015;

	// Compute airfoil
	for (int i = 0; i < nRich; ++i)
	{
		// x/c station
		double xc = cosineSpacing(nRich, i);		

		// Thickness at x/c
		double zt = 5.0*t*(0.2969*sqrt(xc) - 0.1260*xc - 0.3516*pow(xc, 2) + 0.2843*pow(xc, 3) - k5*pow(xc, 4));
		
		// Camber at x/c
		double zc;
		if (xc < p)
			zc = (m / pow(p, 2)) * (2.0*p*xc - pow(xc, 2));
		else
			zc = (m / pow(1 - p, 2))*((1.0 - 2.0*p) + 2.0*p*xc - pow(xc, 2));

		// Compute angle of camber from slope of camber line
		double dzdx;
		if (xc < p)
			dzdx = (2.0*m / pow(p, 2))*(p - xc);
		else
			dzdx = (2.0*m / pow(1 - p, 2))*(p - xc);

		double theta = atan(dzdx);

		// Compute upper and lower points and push-back
		upperPoints.push_back(Vector3(xc - zt * sin(theta), 0.0, zc + zt * cos(theta)));
		lowerPoints.push_back(Vector3(xc + zt * sin(theta), 0.0, zc - zt * cos(theta)));
	}

	// Finish the airfoil
	redistributeAirfoil(n, upperPoints);					// Redistribute upperPoints to the n linearly spaced points
	redistributeAirfoil(n, lowerPoints);					// Redistribute lowerPoints to the n linearly spaced points

	std::reverse(lowerPoints.begin(), lowerPoints.end());	// Reorder lower points from trailing edge to leading edge

	std::vector<Vector3> airfoilPoints = lowerPoints;		// Copy lower points into airfoil points
	for (size_t i = 1; i < upperPoints.size(); ++i)
		airfoilPoints.push_back(upperPoints[i]);			// Add in upper points, skip duplicate leading edge point

	return Airfoil(airfoilPoints);
}

// Create airfoil from file in Selig format - will get redistributed to n linearly spaced ordinates
// Source: https://m-selig.ae.illinois.edu/ads.html
Airfoil Airfoil::readSeligFormat(const std::string& file, int n)
{
	// Vector of upper and lower airfoil points
	std::vector<Vector3> upperPoints;
	std::vector<Vector3> lowerPoints;

	// Open file and read in airfoil
	std::ifstream myFile(file.c_str());
	
	if (myFile.is_open())
	{
		std::string line;
		
		// Title line
		getline(myFile, line);

		// Number of points per side (not used)
		getline(myFile, line);
		
		// Blank line
		getline(myFile, line);

		// Read in the airfoil
		bool onUpper = true;
		while (getline(myFile, line))
		{
			// If the line is empty, we're done with the upper side,
			// so continue reading for the lower side
			if (line.empty())
			{
				onUpper = false;
				continue;
			}

			// Read coordinates from line and store
			double x, z;
			std::stringstream tokens(line);
			tokens >> x >> z;

			if (onUpper)
				upperPoints.push_back(Vector3(x, 0.0, z));				
			else
				lowerPoints.push_back(Vector3(x, 0.0, z));
		}
	}
	else
	{
		std::cerr << "Airfoil::readSeligFormat():File " << file << " cannot be opened." << std::endl;
		exit(EXIT_FAILURE);
	}
	myFile.close();

	// Finish the airfoil
	redistributeAirfoil(n, upperPoints);					// Redistribute upperPoints to the n linearly spaced points
	redistributeAirfoil(n, lowerPoints);					// Redistribute lowerPoints to the n linearly spaced points

	std::reverse(lowerPoints.begin(), lowerPoints.end());	// Reorder lower points from trailing edge to leading edge

	std::vector<Vector3> airfoilPoints = lowerPoints;		// Copy lower points into airfoil points
	for (size_t i = 1; i < upperPoints.size(); ++i)
		airfoilPoints.push_back(upperPoints[i]);			// Add in upper points, skip duplicate leading edge point

	return Airfoil(airfoilPoints);
}

// Redistribute airfoil by linear interpolating to ordinates spaced according to the
// cosine rule.  If an ordinate is outside of the points, they are clamped to the ends
// (no extrapolation).
void Airfoil::redistributeAirfoil(int n, std::vector<Vector3>& points)
{	
	std::vector<Vector3> newPoints;

	for (auto i = 0; i < n; ++i)
	{
		// Compute x value to interpolate to using cosine spacing rule
		double newx = cosineSpacing(n, i);

		// Define a lambda that returns true if the x value of a point is < the x
		// value to interpolate to
		auto lessThan =	[](const Vector3& point, double newx)
		{ 
			return point.x < newx;
		};

		// Find the first points entry whose value is >= x value to interpolate to
		auto iter = std::lower_bound(points.cbegin(), points.cend(), newx, lessThan);

		// If the new x value is greater than the largest x value in points we
		// can't interpolate, snap to end point
		if (iter == points.cend())
		{
			double x = (points.cend() - 1)->x;
			double z = (points.cend() - 1)->z;
			newPoints.push_back(Vector3(x, 0.0, z));
			continue;
		}

		// If the new x value is less than the largest x value in points we
		// can't interpolate, snap to beginning point
		if (iter == points.cbegin() && newx <= points.cbegin()->x)
		{
			double x = points.cbegin()->x;
			double z = points.cbegin()->y;
			newPoints.push_back(Vector3(x, 0.0, z));
			continue;
		}

		// We can interpolate!
		double lowerx = (iter - 1)->x;
		double upperx = iter->x;
		double t = (newx - lowerx) / (upperx - lowerx);
		newPoints.push_back(Vector3::lerp(*(iter - 1), *iter, t));
	}
	
	// Swap newPoints for points
	points.swap(newPoints);
}

// Return ordinate according to Cosine Spacing rule
double Airfoil::cosineSpacing(int n, int i)
{
	return 0.5 * (1 - cos(M_PI * i / (double)(n - 1)));
}
