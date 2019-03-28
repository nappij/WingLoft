// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "FileName.h"

// *****************************************************************************
// Parse Filename
// *****************************************************************************
void FileName::parseFilename(const std::string& file)
{
	// Determine the path
	size_t sep = file.find_last_of("\\/");
	if (sep != std::string::npos)
		path = file.substr(0, sep + 1);
	else
	{
		sep = -1;
		path = ".\\";	// Assume file in working directory if path not given
	}

	// Determine extension
	size_t dot = file.find_last_of(".");
	if (dot != std::string::npos)
		ext = file.substr(dot);
	else
		ext = "";

	// Determine basename
	basename = file.substr(sep + 1, dot - sep - 1);
}