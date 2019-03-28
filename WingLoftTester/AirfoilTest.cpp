// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include <iostream>

#include "Airfoil.h"
#include "TestHarness.h"

// *****************************************************************************
// Static member tests
// *****************************************************************************

// Create a NACA2412 Airfoil
TEST(NACA4, Vector3)
{
	// Test difficult to implement. See AirfoilComparison.xlsx for graphical representation of results.
	// Code below generated result data.

/*
	// NACA 2412 airfoil;
	double t = 0.12;	// t/c
	double m = 0.02;	// max. camber
	double p = 0.4;		// x/c of max. camber

	Airfoil NACA2412 = Airfoil::makeNACA4(20, t, m, p, false);

	// Write it out
	std::cout << NACA2412 << std::endl;
*/
}

// Create a Selig format Airfoil
TEST(selig, Vector3)
{
	// Test difficult to implement. See AirfoilComparison.xlsx for graphical representation of results.
	// Code below generated result data.
/*	
	Airfoil BACJ = Airfoil::readSeligFormat("bacj.dat", 20);

	// Write it out
	std::cout << BACJ;
*/
}
