// ***************************
// *   Introduction to C++   *
// ***************************
//     Author: John Nappi
// Assignment: Final Project
//   Date Due: Apr. 5, 2019

// Contains the path, basename, and extension of a File

#pragma once

#include <string>

class FileName
{
public:
	// Constructors
	FileName() = delete;
	FileName(const std::string& file) { parseFilename(file); };
	
	// Copy constructor and assignment operator
	FileName(const FileName& file) = default;
	FileName& operator=(const FileName& rhs) = default;

	// Destructor
	~FileName() = default;
	
	// Setter Methods
	void setPath(const std::string& path) { this->path = path; }
	void setBasename(const std::string& basename) { this->basename = basename; }
	void setExt(const std::string& ext) { this->ext = ext; }

	// Getter Methods
	const std::string getPath() const { return path; }
	const std::string getBasename() const { return basename; }
	const std::string getExt() const { return ext; }
	const std::string getFullName() const { return path + basename + ext; }	

private:
	void parseFilename(const std::string& file);	// Parse the file name

	std::string path;		// Path of file
	std::string basename;	// Basename of file
	std::string ext;		// Extension of file
};