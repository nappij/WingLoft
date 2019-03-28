// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

// Writes the wing data as a Matlab m-file. Source: https://www.mathworks.com/help/matlab/ref/patch.html

#pragma once

#include <string>

#include "IWriter.h"

class MatlabWriter final : public IWriter
{
public:
	// Constructors
	MatlabWriter() = default;

	// Destructor
	~MatlabWriter() = default;

	// Write method
	void Write(const std::string& file, const Wing& wing) override;
};