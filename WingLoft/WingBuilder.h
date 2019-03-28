// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

// Contains the methods and data needed to build a wing loft.

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Airfoil.h"
#include "Vector3.h"
#include "Wing.h"

class WingBuilder
{
public:
	// Constructors
	WingBuilder() = delete;
	WingBuilder(const FileName& file);

	// Destructor
	virtual ~WingBuilder() = default;

	// Copy constructor and assignment operator
	WingBuilder(const WingBuilder& src) = delete;
	WingBuilder& operator=(const WingBuilder& rhs) = delete;

	// Build the wing
	std::unique_ptr<Wing> buildWing();

private:
	friend class WingBuilderTester;

	int nChord;											// Number of chordwise grids

	// Wing station data
	struct WingStation
	{
		Airfoil airfoil;								// Airfoil shape
		std::string airfoilName;						// Airfoil name
		Vector3 leadingEdgePoint;						// Leading edge point
		double chord;									// Chord length in XY plane
		double twist;									// Twist about quarter chord, degrees
		int nSpan;										// Number of spanwise grids between airfoils
	};
	
	std::vector<WingStation> wingStations;				// All wingstations

	// Grids and connectivity lists
	std::vector<Vector3> grids;							// Grid points
	std::vector<std::vector<int>> connectivity;			// Connectivity table

	// Wing planform file name
	FileName file;

	// Wing building methods
	void readPlanformFile();		// Read and parse planform file
	void buildAirfoilStack();		// Construct and store airfoils
	void loftWing();				// Loft the wing and populate grids
	void buildConnectivity();		// Build the connectivity table
};