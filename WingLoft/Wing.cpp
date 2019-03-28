// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "Wing.h"

// *****************************************************************************
// Grid and connectivity setter
// *****************************************************************************

// Set the grid table and connectivity table together
void Wing::setGridsAndConnectivity(const std::vector<Vector3>& grids, 
	const std::vector<std::vector<int>>& connectivity)
{
	this->grids = grids;
	this->connectivity = connectivity;
}

// *****************************************************************************
// Grid and connectivity getters
// *****************************************************************************

// Return grid table
const std::vector<Vector3>& Wing::getGrids() const
{
	return grids;
}

// Return connectivity table
const std::vector<std::vector<int>>& Wing::getConnectivity() const
{
	return connectivity;
}