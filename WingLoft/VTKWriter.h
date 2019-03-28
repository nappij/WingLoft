// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

// Writes the wing data in the VTK file format. Source: https://vtk.org/wp-content/uploads/2015/04/file-formats.pdf

#pragma once

#include <string>

#include "IWriter.h"

class VTKWriter final : public IWriter
{
public:
	// Constructors
	VTKWriter() = default;
	
	// Destructor
	~VTKWriter() = default;

	// Write method
	void Write(const std::string& file, const Wing& wing) override;
};

