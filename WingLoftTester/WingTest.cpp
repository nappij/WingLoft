// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "Wing.h"
#include "TestHarness.h"

// Global tolerance value
const static double TOL = 1.0e-6;

// *****************************************************************************
// Getter Tests
// *****************************************************************************
TEST(getGrids, Wing)
{
	// Make some grids
	std::vector<Vector3> grids;
	grids.push_back(Vector3(1.0, 2.0, 3.0));
	grids.push_back(Vector3(4.0, 5.0, 6.0));

	// Empty connectivity table
	std::vector<std::vector<int>> connectivity;

	Wing myWing;
	myWing.setGridsAndConnectivity(grids, connectivity);

	// Check grids
	CHECK_DOUBLES_EQUAL(1.0, myWing.getGrids()[0].x, TOL);	
	CHECK_DOUBLES_EQUAL(2.0, myWing.getGrids()[0].y, TOL);
	CHECK_DOUBLES_EQUAL(3.0, myWing.getGrids()[0].z, TOL);
	CHECK_DOUBLES_EQUAL(4.0, myWing.getGrids()[1].x, TOL);
	CHECK_DOUBLES_EQUAL(5.0, myWing.getGrids()[1].y, TOL);
	CHECK_DOUBLES_EQUAL(6.0, myWing.getGrids()[1].z, TOL);
}

TEST(getConnectivity, Wing)
{
	// Empty grid table
	std::vector<Vector3> grids;

	// Make a connectivity table
	std::vector<std::vector<int>> connectivity;
	std::vector<int> element1 = { 0, 1, 2, 3 };
	std::vector<int> element2 = { 7, 6, 5, 4 };
	connectivity.push_back(element1);
	connectivity.push_back(element2);

	Wing myWing;
	myWing.setGridsAndConnectivity(grids, connectivity);

	// Check connectivity
	CHECK_EQUAL(0, myWing.getConnectivity()[0][0]);
	CHECK_EQUAL(1, myWing.getConnectivity()[0][1]);
	CHECK_EQUAL(2, myWing.getConnectivity()[0][2]);
	CHECK_EQUAL(3, myWing.getConnectivity()[0][3]);
	CHECK_EQUAL(7, myWing.getConnectivity()[1][0]);
	CHECK_EQUAL(6, myWing.getConnectivity()[1][1]);
	CHECK_EQUAL(5, myWing.getConnectivity()[1][2]);
	CHECK_EQUAL(4, myWing.getConnectivity()[1][3]);
}
