// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "FileName.h"
#include "TestHarness.h"

// *****************************************************************************
// Constructor Tests
// *****************************************************************************
TEST(normalFile, FileName)
{
	// Normal file name
	FileName myFile("C:\\windows\\cool.exe");
	
	CHECK_EQUAL("C:\\windows\\", myFile.getPath());
	CHECK_EQUAL("cool", myFile.getBasename());
	CHECK_EQUAL(".exe", myFile.getExt());
	CHECK_EQUAL("C:\\windows\\cool.exe", myFile.getFullName());
}

TEST(noPath, FileName)
{
	// No path
	FileName myFile("weird.bat");
	CHECK_EQUAL(".\\", myFile.getPath());
	CHECK_EQUAL("weird", myFile.getBasename());
	CHECK_EQUAL(".bat", myFile.getExt());
	CHECK_EQUAL(".\\weird.bat", myFile.getFullName());
}

TEST(noExt, FileName)
{
	// No extension
	FileName myFile("C:\\windows\\cool");

	CHECK_EQUAL("C:\\windows\\", myFile.getPath());
	CHECK_EQUAL("cool", myFile.getBasename());
	CHECK_EQUAL("", myFile.getExt());
	CHECK_EQUAL("C:\\windows\\cool", myFile.getFullName());
}

TEST(noPathNoExt, FileName)
{
	// No path or extension
	FileName myFile("neato");

	CHECK_EQUAL(".\\", myFile.getPath());
	CHECK_EQUAL("neato", myFile.getBasename());
	CHECK_EQUAL("", myFile.getExt());
	CHECK_EQUAL(".\\neato", myFile.getFullName());
}
