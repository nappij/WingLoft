// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include "VTKWriter.h"

// *****************************************************************************
// Write Implementation
// *****************************************************************************

// Source: https://vtk.org/wp-content/uploads/2015/04/file-formats.pdf
void VTKWriter::Write(const std::string& file, const Wing& wing)
{
	// Open .vtk file for writing
	std::ofstream myFile(file.c_str());

	if (myFile.is_open())
	{
		// Write out header
		myFile << "# vtk DataFile Version 2.0" << std::endl;
		myFile << "FieldData" << std::endl;
		myFile << "ASCII" << std::endl;
		myFile << "DATASET UNSTRUCTURED_GRID" << std::endl;
		
		// Write out the points
		myFile << "POINTS " << wing.getGrids().size() << " double" << std::endl;
		for (const auto& grid : wing.getGrids())
			myFile << grid.x << " " << grid.y << " " << grid.z << std::endl;
		myFile << std::endl;

		// Compute number of cells
		size_t nPanels = 0;
		size_t sizePerPanel = 0;
		for (const auto& element : wing.getConnectivity())
		{
			nPanels += 1;
			sizePerPanel += element.size() + 1;
		}			

		// Write out the cells
		myFile << "CELLS " << nPanels << " " << sizePerPanel << std::endl;
		for (const auto& element : wing.getConnectivity())
		{
			myFile << element.size();
			for (const auto& v : element)
			{				
				myFile << " " << v;
			}
			myFile << std::endl;
		}
		myFile << std::endl;

		// Write out the cell types
		myFile << "CELL_TYPES " << nPanels << std::endl;
		for (const auto& element : wing.getConnectivity())
		{
			// VTK_QUAD = 9
			myFile << "9" << std::endl;
		}
	}
	myFile.close();
}
