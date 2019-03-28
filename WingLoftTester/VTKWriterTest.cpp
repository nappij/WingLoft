// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "VTKWriter.h"
#include "Wing.h"
#include "WingBuilder.h"
#include "TestHarness.h"

// *****************************************************************************
// VTKWriter Test
// *****************************************************************************
TEST(write, VTKWriter)
{
	// Build the wing
	FileName file("CRM_planform.dat");
	WingBuilder myWingBuilder(file);
	std::unique_ptr<Wing> myWingPtr = myWingBuilder.buildWing();

	// Write the wing
	VTKWriter vtkWriter;
	file.setExt(".vtk"),
	vtkWriter.Write(file.getFullName(), *myWingPtr);
}
