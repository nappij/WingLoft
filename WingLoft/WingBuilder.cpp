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

#include "WingBuilder.h"

// *****************************************************************************
// Constructor
// *****************************************************************************
WingBuilder::WingBuilder(const FileName& file)
	: file(file)
{
}

// *****************************************************************************
// Wing Builder Methods
// *****************************************************************************

// Main driver that chains the builder method calls
std::unique_ptr<Wing> WingBuilder::buildWing()
{
	// Read in the planform file and parse it
	readPlanformFile();

	// Build the airfoil stack
	buildAirfoilStack();

	// Loft the wing and populate grids
	loftWing();

	// Build connectivity
	buildConnectivity();

	// Create the wing and set grids and connectivity
	std::unique_ptr<Wing> wing = std::make_unique<Wing>();
	wing->setGridsAndConnectivity(grids, connectivity);
	return wing;
}

// Read and parse the planform file
void WingBuilder::readPlanformFile()
{
	// open file and read in planform
	std::ifstream myFile(file.getFullName());

	if (myFile.is_open())
	{
		std::string line;

		// Title line - not used
		getline(myFile, line);

		// Number of chordwise points
		getline(myFile, line);
		std::stringstream tokens(line);
		tokens >> nChord;

		// Read in the rest of the file
		while (getline(myFile, line))
		{
			std::stringstream tokens(line);

			// Declare new wing station
			WingStation wingStation;

			// Leading edge points
			double xle, yle, zle;
			tokens >> xle >> yle >> zle;		
			wingStation.leadingEdgePoint = Vector3(xle, yle, zle);

			// Chord length
			double chord;
			tokens >> chord;
			wingStation.chord = chord;

			// Quarter chord twist
			double twist;
			tokens >> twist;
			wingStation.twist = twist;

			// Airfoil name
			std::string airfoilName;
			tokens >> airfoilName;
			wingStation.airfoilName = airfoilName;

			// Number of span grids to next station
			int nSpan;
			tokens >> nSpan;
			wingStation.nSpan = nSpan;

			wingStations.push_back(wingStation);
		}
	} 
	else
	{
		std::cerr << "WingBuilder::readPlanformFile():File " << file.getFullName() << " cannot be opened." << std::endl;
		exit(EXIT_FAILURE);
	}
	myFile.close();
}

// Build up the non-dimensionalized airfoils at each wing station
void WingBuilder::buildAirfoilStack()
{
	// Build stack of airfoils
	for (auto& wingStation : wingStations)
	{
		// Get the airfoil name
		const std::string& airfoilName = wingStation.airfoilName;

		// Is this a NACA4 airfoil?
		bool isNACA4 = (airfoilName.find("NACA") == 0)
			&& !(airfoilName.find(".dat") == 0);	// True for NACAXXXX but not NACAXXXX.dat which is a file.

		if (isNACA4)
		{
			// Parse out NACA 4 parameters
			std::stringstream tokens(airfoilName.substr(4, 1) + " "
				+ airfoilName.substr(5, 1) + " " + airfoilName.substr(6, 2));

			// Maximum camber, location of max. camber, max. thickness
			double m, p, t;
			tokens >> m >> p >> t;
			m /= 100.0;
			p /= 10.0;
			t /= 100.0;

			// Generate NACA4 airfoil and add it to the wing station
			wingStation.airfoil = Airfoil::makeNACA4(nChord, t, m, p);
		}
		else
		{
			// Read airfoil from file and push to the stack. Files assumed to be in same directory
			// as wing planform file.
			std::string fullName = file.getPath() + airfoilName;
			wingStation.airfoil = Airfoil::readSeligFormat(fullName, nChord);
		}
	}
}

// Transform the airfoils according the planform data and compute the wing grids
void WingBuilder::loftWing()
{
	// Unit vector for wing plane twist direction
	Vector3 unitY(0.0, 1.0, 0.0);

	// Non-dimensionalized quarter chord point
	Vector3 origin(0.25, 0.0, 0.0);

	// Transform the airfoils according to the wing planform parameters
	for (auto& wingStation : wingStations)
	{
		// Get the airfoil
		Airfoil& airfoil = wingStation.airfoil;

		// Twist airfoil about the quarter chord        
		double twist = wingStation.twist * M_PI / 180.0;
		airfoil.rotate(unitY, twist, origin);

		// Scale airfoil by chord length
		double chord = wingStation.chord;
		airfoil.scale(chord);

		// Move airfoil to leading edge
		airfoil.translate(wingStation.leadingEdgePoint);
	}

	// Interpolate the airfoils and push to grids
	for (std::vector<WingStation>::iterator it = wingStations.begin(); it != wingStations.end() - 1; ++it)
	{
		Airfoil& ibAirfoil = it->airfoil;
		Airfoil& obAirfoil = (it + 1)->airfoil;

		// Push back inboard airfoil to grids
		for (const auto& point : ibAirfoil.getPoints())
			grids.push_back(point);

		// Push back intermediate airfoils to grids
		for (int j = 1; j < it->nSpan; ++j)
		{
			double t = j / double(it->nSpan);
			Airfoil midAirfoil = Airfoil::lerp(ibAirfoil, obAirfoil, t);
			for (const auto& point : midAirfoil.getPoints())
				grids.push_back(point);
		}
	}
	
	// Push back tip airfoil to grids
	Airfoil& tipAirfoil = wingStations.back().airfoil;
	for (const auto& point : tipAirfoil.getPoints())
		grids.push_back(point);

	// Push back closed tip to grids
	for (size_t i = 0; i < tipAirfoil.getPoints().size(); ++i)
	{
		Vector3 point1 = tipAirfoil[i];
		Vector3 point2 = tipAirfoil[tipAirfoil.getPoints().size() - 1 - i];
		grids.push_back((point1 + point2) / 2.0);
	}
}

// Build the connectivity table - since the grid is structured, the algorithm
// to compute the connectivity is fairly simple
void WingBuilder::buildConnectivity()
{
	// Compute number of chordwise and spanwise elements
	int nPtsPerAirfoil = (2 * nChord - 1);
	int nChordElements = nPtsPerAirfoil - 1;
	
	int nSpanElements = 0;
	for (std::vector<WingStation>::iterator it = wingStations.begin(); it != wingStations.end() - 1; ++it)
		nSpanElements += it->nSpan;
	nSpanElements += 1;		// Add 1 more to account for the closed tip grids

	// Compute connectivity table values
	for (int j = 0; j < nSpanElements; ++j)
	{
		for (int i = 0; i < nChordElements; ++i)
		{
			std::vector<int> element;
			element.push_back(i + j*nPtsPerAirfoil);
			element.push_back((i + 1) + j*nPtsPerAirfoil);
			element.push_back((i + 1) + (j + 1)*nPtsPerAirfoil);
			element.push_back(i + (j + 1)*nPtsPerAirfoil);
			connectivity.push_back(element);
		}
	}
}