// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

// Contains the methods and data needed to build a wing loft.

#pragma once

#include <string>
#include <vector>

#include "Airfoil.h"
#include "FileName.h"
#include "Vector3.h"

class Wing
{
public:
	// Constructor
	Wing() = default;
	
	// Destructor
	~Wing() = default;

	// Copy constructor and assignment operator
	Wing(const Wing& src) = delete;
	Wing& operator=(const Wing& rhs) = delete;

	// Setter function for grids and connectivity
	void setGridsAndConnectivity(const std::vector<Vector3>& grids, const std::vector <std::vector<int>>& connectivity);

	// Getter functions for grids and connectivity
	const std::vector<Vector3>& getGrids() const;
	const std::vector<std::vector<int>>& getConnectivity() const;

private:
	// Grids and connectivity tables
	std::vector<Vector3> grids;
	std::vector<std::vector<int>> connectivity;
};

