// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

// Contains the interface that a specialized writer class must implement.

#pragma once

#include <fstream>
#include <string>

#include "Wing.h"

class IWriter
{
public:
	// Constructor
	IWriter() = default;

	// Destructor
	virtual ~IWriter() = default;

	// Write function to implement
	virtual void Write(const std::string& file, const Wing& wing) = 0;
};

