// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "FileName.h"
#include "MatlabWriter.h"
#include "VTKWriter.h"
#include "Wing.h"
#include "WingBuilder.h"

// Loft that wing!
int main(int argc, char *argv[])
{
	// Parse the arguments
	if (argc < 3 || argc > 4)
	{
		std::cerr << "Illegal number of arguments. Usage:" << std::endl << std::endl;
		std::cerr << "WINGLOFT inputfile [-v] [-m]" << std::endl << std::endl;
		std::cerr << "  inputfile  Specifies the wing planform file.  If full path not" << std::endl;
		std::cerr << "             specified, file is assume to be in working directory." << std::endl;
		std::cerr << "  -v         Outputs wing loft in a .vtk file with same basename as" << std::endl;
		std::cerr << "             inputfile." << std::endl;
		std::cerr << "  -m         Outputs wing loft in a .m file with same basename as" << std::endl;
		std::cerr << "             inputfile." << std::endl << std::endl;
		std::cerr << "At least one of -v or -m must be present, but both can be specified." << std::endl;

		return EXIT_FAILURE;
	}

	FileName file(argv[1]);				// Wing planform file
	std::vector<std::string> argFlags;
	for (int i = 2; i < argc; ++i)
		argFlags.push_back(argv[i]);	// Output file request flags

	// Create a wing builder and build that wing
	WingBuilder wingBuilder(file);
	std::shared_ptr<Wing> wingPtr = wingBuilder.buildWing();

	// Write the output files
	for (const auto& argFlag : argFlags)
	{
		if (argFlag.find("-m") == 0)
		{
			// Output Matlab m-file
			MatlabWriter matlabWriter;
			file.setExt(".m"),
			matlabWriter.Write(file.getFullName(), *wingPtr);
		}
		else if (argFlag.find("-v") == 0)
		{
			// Output VTK file
			VTKWriter vtkWriter;
			file.setExt(".vtk"),
			vtkWriter.Write(file.getFullName(), *wingPtr);
		}
		else
		{
			std::cerr << "Invalid output request flag: " << argFlag << std::endl;
			return EXIT_FAILURE;
		}
		std::cout << "Done writing " << file.getFullName() << "!" << std::endl;
	}
	return EXIT_SUCCESS;
}