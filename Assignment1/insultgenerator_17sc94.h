/*
 * insultgenerator_17sc94.h
 *
 *      Author: Sydney Caulfeild
 *      Date: 10/1/2020
 *      This file contains the declarations for all classes used in assignment 1. The following classes are declared:
 *      InsultGenerator Class - used to generate between 1 and 10,000 randomized "Shakesperian" insults.
 *      FileException Class - an exception class used to throw exceptions relating to file input/output.
 *      NumInsultsOutOfBounds Class - an exception class used to throw exceptions when an invalid number of insults are requested.
 */

#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;

class InsultGenerator {
public:
	// This member function reads words from InsultsSource.txt and saves them in 3 arrays. Each column is saved in its own array.
	void initialize();
	// talkToMe() will generate and return a single insult.
	string talkToMe();
	// This member function will generate the number of insults provided and return them in a vector in alphabetical order with no duplicates.
	vector<string> generate(const int numInsults);
	// This member function uses generate() to generate the requested number of insults and also saves the insults to a specified file.
	vector<string> generateAndSave(const string fileName, const int numInsults);
private:
	// Each column array stores one column from the InsultsSource.txt file.
	string wordColumn1[50];
	string wordColumn2[50];
	string wordColumn3[50];
	// This map contains integer keys that represent the indices of each word in their column array and string values that contain the insult.
	map<int, string> insultIndicesAndValues;
};

// An exception of this type will be thrown if a file to be read/written to cannot be opened.
class FileException {
public:
	FileException(const string& message);
	string& what();
private:
	string message;
};

// An exception of this type will be thrown if the user requests to generate less than 1 or more than 10000 insults.
class NumInsultsOutOfBounds {
public:
	NumInsultsOutOfBounds(const string& message);
	string& what();
private:
	string message;
};

