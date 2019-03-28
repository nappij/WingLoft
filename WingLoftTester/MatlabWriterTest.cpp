// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "MatlabWriter.h"
#include "Wing.h"
#include "WingBuilder.h"
#include "TestHarness.h"

// *****************************************************************************
// MatlabWriter Test
// *****************************************************************************
TEST(write, MatlabWriter)
{
	// Build the wing
	FileName file("CRM_planform.dat");
	WingBuilder myWingBuilder(file);
	std::unique_ptr<Wing> myWingPtr = myWingBuilder.buildWing();
	
	// Write the wing
	MatlabWriter matlabWriter;	
	file.setExt(".m"),
	matlabWriter.Write(file.getFullName(), *myWingPtr);
}
