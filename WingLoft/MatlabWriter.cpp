// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "MatlabWriter.h"

// *****************************************************************************
// Write Implementation
// *****************************************************************************

// Source: https://www.mathworks.com/help/matlab/ref/patch.html
void MatlabWriter::Write(const std::string& file, const Wing& wing)
{
	// Open .m file for writing
	std::ofstream myFile(file.c_str());

	if (myFile.is_open())
	{
		// Write out the header
		myFile << "% WingLoft Patch Plot" << std::endl;
		myFile << "clear; close all; clc;" << std::endl;
		myFile << std::endl;

		// Write out the vertices
		myFile << "%% Vertices" << std::endl;
		myFile << "V = [" << std::endl;
		for (const auto& grid : wing.getGrids())
			myFile << grid.x << " " << grid.y << " " << grid.z << std::endl;
		myFile << "];" << std::endl << std::endl;

		// Write out the connectivity table
		myFile << "%% Faces" << std::endl;
		myFile << "F = [" << std::endl;
		for (const auto& element : wing.getConnectivity())
		{
			for (const auto& v : element)
				myFile << v + 1 << " ";
			myFile << std::endl;
		}
		myFile << "];" << std::endl << std::endl;

		// Write out patch plot
		myFile << "%% Patch Plot" << std::endl;
		myFile << "p = patch('Vertices', V, 'Faces', F, 'FaceColor', [0,1,1], 'FaceLighting', 'Gouraud');" << std::endl;
		myFile << "axis equal;" << std::endl;
		myFile << "grid on;" << std::endl;
		myFile << "xlabel('X');" << std::endl;
		myFile << "ylabel('Y');" << std::endl;
		myFile << "zlabel('Z');" << std::endl;
	}
	myFile.close();
}
