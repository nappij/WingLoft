// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "FileName.h"
#include "Wing.h"
#include "WingBuilder.h"
#include "TestHarness.h"

// NOTE: The method buildWing() is tested in the MatlabWriterTest and VTKWriterTest files

// Global tolerance value
const static double TOL = 1.0e-5;

// *****************************************************************************
// Wing Builder Tester Class
// *****************************************************************************
// This class is a friend of the WingBuilder class, and exposes its private
// data and methods for testing.

class WingBuilderTester
{
public:
	// Constructors
	WingBuilderTester() = delete;
	WingBuilderTester(const FileName& file) : wingBuilder(std::make_unique<WingBuilder>(file)) {};

	// Destructor
	virtual ~WingBuilderTester() = default;

	// Wing Builder functions
	void readPlanformFile() { wingBuilder->readPlanformFile(); }
	void buildAirfoilStack() { wingBuilder->buildAirfoilStack(); }
	void loftWing() { wingBuilder->loftWing(); }
	void buildConnectivity() { wingBuilder->buildConnectivity(); }

	// Getter functions
	const FileName getFile() const { return wingBuilder->file; }
	const int getNChord() { return wingBuilder->nChord; }
	const std::vector<WingBuilder::WingStation> getWingStations() const { return wingBuilder->wingStations; }
	const std::vector<Vector3> getGrids() const { return wingBuilder->grids; }
	const std::vector<std::vector<int>> getConnectivity() const { return wingBuilder->connectivity; }

private:
	std::unique_ptr<WingBuilder> wingBuilder;
};

// *****************************************************************************
// Test Wing
// *****************************************************************************
std::unique_ptr<Wing> testWingPtr;

// *****************************************************************************
// Test WingBuilder
// *****************************************************************************
const FileName wingFile(".\\test input\\test_planform.dat");
WingBuilderTester wingBuilderTester(wingFile);

// *****************************************************************************
// WingBuilder Constructor Test
// *****************************************************************************
TEST(constructor, WingBuilder)
{
	CHECK_EQUAL(".\\test input\\test_planform.dat", wingBuilderTester.getFile().getFullName());
}

// *****************************************************************************
// WingBuilder Builder Tests
// *****************************************************************************
TEST(readPlanformFile, WingBuilder)
{
	wingBuilderTester.readPlanformFile();
	
	// Check nChords
	CHECK_EQUAL(4, wingBuilderTester.getNChord());

	// Check first planform line
	CHECK_EQUAL("testfoil.dat", wingBuilderTester.getWingStations()[0].airfoilName);
	CHECK_EQUAL(0.0, wingBuilderTester.getWingStations()[0].leadingEdgePoint.x);
	CHECK_EQUAL(0.0, wingBuilderTester.getWingStations()[0].leadingEdgePoint.y);
	CHECK_EQUAL(0.0, wingBuilderTester.getWingStations()[0].leadingEdgePoint.z);
	CHECK_EQUAL(10.0, wingBuilderTester.getWingStations()[0].chord);
	CHECK_EQUAL(-1.0, wingBuilderTester.getWingStations()[0].twist);
	CHECK_EQUAL(2, wingBuilderTester.getWingStations()[0].nSpan);

	// Check second planform line
	CHECK_EQUAL("testfoil.dat", wingBuilderTester.getWingStations()[1].airfoilName);
	CHECK_EQUAL(0.0, wingBuilderTester.getWingStations()[1].leadingEdgePoint.x);
	CHECK_EQUAL(10.0, wingBuilderTester.getWingStations()[1].leadingEdgePoint.y);
	CHECK_EQUAL(5.0, wingBuilderTester.getWingStations()[1].leadingEdgePoint.z);
	CHECK_EQUAL(5.0, wingBuilderTester.getWingStations()[1].chord);
	CHECK_EQUAL(3.0, wingBuilderTester.getWingStations()[1].twist);
	CHECK_EQUAL(-1, wingBuilderTester.getWingStations()[1].nSpan);
}

TEST(buildAirfoilStack, WingBuilder)
{
	wingBuilderTester.buildAirfoilStack();

	// Check first airfoil
	CHECK_DOUBLES_EQUAL(1.0, wingBuilderTester.getWingStations()[0].airfoil[0].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getWingStations()[0].airfoil[0].z, TOL);
	CHECK_DOUBLES_EQUAL(0.75, wingBuilderTester.getWingStations()[0].airfoil[1].x, TOL);
	CHECK_DOUBLES_EQUAL(-0.06, wingBuilderTester.getWingStations()[0].airfoil[1].z, TOL);
	CHECK_DOUBLES_EQUAL(0.25, wingBuilderTester.getWingStations()[0].airfoil[2].x, TOL);
	CHECK_DOUBLES_EQUAL(-0.06, wingBuilderTester.getWingStations()[0].airfoil[2].z, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getWingStations()[0].airfoil[3].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getWingStations()[0].airfoil[3].z, TOL);
	CHECK_DOUBLES_EQUAL(0.25, wingBuilderTester.getWingStations()[0].airfoil[4].x, TOL);
	CHECK_DOUBLES_EQUAL(0.06, wingBuilderTester.getWingStations()[0].airfoil[4].z, TOL);
	CHECK_DOUBLES_EQUAL(0.75, wingBuilderTester.getWingStations()[0].airfoil[5].x, TOL);
	CHECK_DOUBLES_EQUAL(0.06, wingBuilderTester.getWingStations()[0].airfoil[5].z, TOL);
	CHECK_DOUBLES_EQUAL(1.0, wingBuilderTester.getWingStations()[0].airfoil[6].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getWingStations()[0].airfoil[6].z, TOL);

	// Check one point of second airfoil since it should be the same.
	CHECK_DOUBLES_EQUAL(0.25, wingBuilderTester.getWingStations()[1].airfoil[2].x, TOL);
	CHECK_DOUBLES_EQUAL(-0.06, wingBuilderTester.getWingStations()[1].airfoil[2].z, TOL);
}

TEST(loftWing, WingBuilder)
{
	wingBuilderTester.loftWing();

	// Computing the expected values was done "by hand" in Excel. It was brutal.
	
	// Check the first airfoil
	CHECK_DOUBLES_EQUAL(9.99886, wingBuilderTester.getGrids()[0].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getGrids()[0].y, TOL);
	CHECK_DOUBLES_EQUAL(0.130893, wingBuilderTester.getGrids()[0].z, TOL);
	CHECK_DOUBLES_EQUAL(7.50971, wingBuilderTester.getGrids()[1].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getGrids()[1].y, TOL);
	CHECK_DOUBLES_EQUAL(-0.512647, wingBuilderTester.getGrids()[1].z, TOL);
	CHECK_DOUBLES_EQUAL(2.51047, wingBuilderTester.getGrids()[2].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getGrids()[2].y, TOL);
	CHECK_DOUBLES_EQUAL(-0.599909, wingBuilderTester.getGrids()[2].z, TOL);
	CHECK_DOUBLES_EQUAL(0.000380762, wingBuilderTester.getGrids()[3].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getGrids()[3].y, TOL);
	CHECK_DOUBLES_EQUAL(-0.043631, wingBuilderTester.getGrids()[3].z, TOL);
	CHECK_DOUBLES_EQUAL(2.48953, wingBuilderTester.getGrids()[4].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getGrids()[4].y, TOL);
	CHECK_DOUBLES_EQUAL(0.599909, wingBuilderTester.getGrids()[4].z, TOL);
	CHECK_DOUBLES_EQUAL(7.48877, wingBuilderTester.getGrids()[5].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getGrids()[5].y, TOL);
	CHECK_DOUBLES_EQUAL(0.687171, wingBuilderTester.getGrids()[5].z, TOL);
	CHECK_DOUBLES_EQUAL(9.99886, wingBuilderTester.getGrids()[6].x, TOL);
	CHECK_DOUBLES_EQUAL(0.0, wingBuilderTester.getGrids()[6].y, TOL);
	CHECK_DOUBLES_EQUAL(0.130893, wingBuilderTester.getGrids()[6].z, TOL);

	// Check the intermediate airfoil
	CHECK_DOUBLES_EQUAL(7.49686, wingBuilderTester.getGrids()[7].x, TOL);
	CHECK_DOUBLES_EQUAL(5.0, wingBuilderTester.getGrids()[7].y, TOL);
	CHECK_DOUBLES_EQUAL(2.46732, wingBuilderTester.getGrids()[7].z, TOL);
	CHECK_DOUBLES_EQUAL(5.62029, wingBuilderTester.getGrids()[8].x, TOL);
	CHECK_DOUBLES_EQUAL(5.0, wingBuilderTester.getGrids()[8].y, TOL);
	CHECK_DOUBLES_EQUAL(2.02846, wingBuilderTester.getGrids()[8].z, TOL);
	CHECK_DOUBLES_EQUAL(1.87239, wingBuilderTester.getGrids()[9].x, TOL);
	CHECK_DOUBLES_EQUAL(5.0, wingBuilderTester.getGrids()[9].y, TOL);
	CHECK_DOUBLES_EQUAL(2.05025, wingBuilderTester.getGrids()[9].z, TOL);
	CHECK_DOUBLES_EQUAL(0.00104692, wingBuilderTester.getGrids()[10].x, TOL);
	CHECK_DOUBLES_EQUAL(5.0, wingBuilderTester.getGrids()[10].y, TOL);
	CHECK_DOUBLES_EQUAL(2.51089, wingBuilderTester.getGrids()[10].z, TOL);
	CHECK_DOUBLES_EQUAL(1.87761, wingBuilderTester.getGrids()[11].x, TOL);
	CHECK_DOUBLES_EQUAL(5.0, wingBuilderTester.getGrids()[11].y, TOL);
	CHECK_DOUBLES_EQUAL(2.94975, wingBuilderTester.getGrids()[11].z, TOL);
	CHECK_DOUBLES_EQUAL(5.62552, wingBuilderTester.getGrids()[12].x, TOL);
	CHECK_DOUBLES_EQUAL(5.0, wingBuilderTester.getGrids()[12].y, TOL);
	CHECK_DOUBLES_EQUAL(2.92796, wingBuilderTester.getGrids()[12].z, TOL);
	CHECK_DOUBLES_EQUAL(7.49686, wingBuilderTester.getGrids()[13].x, TOL);
	CHECK_DOUBLES_EQUAL(5.0, wingBuilderTester.getGrids()[13].y, TOL);
	CHECK_DOUBLES_EQUAL(2.46732, wingBuilderTester.getGrids()[13].z, TOL);

	// Check the last airfoil
	CHECK_DOUBLES_EQUAL(4.99486, wingBuilderTester.getGrids()[14].x, TOL);
	CHECK_DOUBLES_EQUAL(10.0, wingBuilderTester.getGrids()[14].y, TOL);
	CHECK_DOUBLES_EQUAL(4.80374, wingBuilderTester.getGrids()[14].z, TOL);
	CHECK_DOUBLES_EQUAL(3.73087, wingBuilderTester.getGrids()[15].x, TOL);
	CHECK_DOUBLES_EQUAL(10.0, wingBuilderTester.getGrids()[15].y, TOL);
	CHECK_DOUBLES_EQUAL(4.56957, wingBuilderTester.getGrids()[15].z, TOL);
	CHECK_DOUBLES_EQUAL(1.2343, wingBuilderTester.getGrids()[16].x, TOL);
	CHECK_DOUBLES_EQUAL(10.0, wingBuilderTester.getGrids()[16].y, TOL);
	CHECK_DOUBLES_EQUAL(4.70041, wingBuilderTester.getGrids()[16].z, TOL);
	CHECK_DOUBLES_EQUAL(0.00171308, wingBuilderTester.getGrids()[17].x, TOL);
	CHECK_DOUBLES_EQUAL(10.0, wingBuilderTester.getGrids()[17].y, TOL);
	CHECK_DOUBLES_EQUAL(5.06542, wingBuilderTester.getGrids()[17].z, TOL);
	CHECK_DOUBLES_EQUAL(1.2657, wingBuilderTester.getGrids()[18].x, TOL);
	CHECK_DOUBLES_EQUAL(10.0, wingBuilderTester.getGrids()[18].y, TOL);
	CHECK_DOUBLES_EQUAL(5.29959, wingBuilderTester.getGrids()[18].z, TOL);
	CHECK_DOUBLES_EQUAL(3.76227, wingBuilderTester.getGrids()[19].x, TOL);
	CHECK_DOUBLES_EQUAL(10.0, wingBuilderTester.getGrids()[19].y, TOL);
	CHECK_DOUBLES_EQUAL(5.16875, wingBuilderTester.getGrids()[19].z, TOL);
	CHECK_DOUBLES_EQUAL(4.99486, wingBuilderTester.getGrids()[20].x, TOL);
	CHECK_DOUBLES_EQUAL(10.0, wingBuilderTester.getGrids()[20].y, TOL);
	CHECK_DOUBLES_EQUAL(4.80374, wingBuilderTester.getGrids()[20].z, TOL);
}

TEST(buildConnectivity, WingBuilder)
{
	wingBuilderTester.buildConnectivity();

	// Just check the connectivity table between the first two airfoils

	// Computing the expected values was done "by hand" in Excel. It was brutal.
	std::string expected("0 1 8 7 1 2 9 8 2 3 10 9 3 4 11 10 4 5 12 11 5 6 13 12 ");

	std::stringstream actual;
	for (size_t i = 0; i < 6; ++i)
		for (size_t j = 0; j < 4; ++j)
			actual << wingBuilderTester.getConnectivity()[i][j] << " ";
	
	CHECK_EQUAL(expected, actual.str());
}