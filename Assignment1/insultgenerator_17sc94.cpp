/*
 * insultgenerator_17sc94.cpp
 *
 *      Author: Sydney Caulfeild
 *      Date: 10/1/2020
 *      This file implements all classes used in assignment 1. The following classes are implemented:
 *      InsultGenerator Class - used to generate between 1 and 10,000 randomized "Shakesperian" insults.
 *      FileException Class - an exception class used to throw exceptions relating to file input/output.
 *      NumInsultsOutOfBounds Class - an exception class used to throw exceptions when an invalid number of insults are requested.
 */

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "insultgenerator_17sc94.h"

using namespace std;

/*
 * Implementation of methods in the InsultGenerator class.
 */

void InsultGenerator::initialize() {
	// Seed the random number generator.
	srand ( time(NULL) );
	// Read file into inFile variable.
	ifstream inFile("src\\InsultsSource.txt");
	int i = 0;
	string col1, col2, col3;
	if (inFile.is_open()) {
		// Loop through each line and save words in the appropriate column.
		while (inFile >> col1 >> col2 >> col3) {
			wordColumn1[i] = col1;
			wordColumn2[i] = col2;
			wordColumn3[i] = col3;
			i++;
		}
		inFile.close();
		return;
	}
	else {
		// Throw a FileException if inFile was unable to open.
		throw FileException("Can't open file: InsultsSource.txt.\n");
	}
}

string InsultGenerator::talkToMe() {
	int n1 = rand() % 50;
	int n2 = rand() % 50;
	int n3 = rand() % 50;
	return "Thou " + wordColumn1[n1] + " " + wordColumn2[n2] + " " + wordColumn3[n3] + "!\n";
}

vector<string> InsultGenerator::generate(const int numInsults) {
	// Check to make sure the requested number of insults is valid.
	if (numInsults < 1) {
		throw NumInsultsOutOfBounds("Your requested number of insults must be greater than 0.\n");
	}
	else if (numInsults > 10000) {
		throw NumInsultsOutOfBounds("Your requested number of insults must be no greater than 10000.\n");
	}

	// Declare a vector to be returned.
	vector<string> returnInsults;
	for (int i = 0; i < numInsults; i ++) {
		int n1 = rand() % 50;
		int n2 = rand() % 50;
		int n3 = rand() % 50;

		int key = n1*10000 + n2*100 + n3;
		string value = "Thou " + wordColumn1[n1] + " " + wordColumn2[n2] + " " + wordColumn3[n3] + "!\n";
		// A map is used because it will eliminate duplicate insults (no duplicate keys are allowed) and it will order the
		// insults in alphabetical order since the keys are integers that will be sorted in increasing order (and in the column
		// arrays, 'a' is at index 0).
		insultIndicesAndValues.insert(std::pair<int,string>(key,value) );
	}
	map<int, string>::iterator it;
	// Copy the alphabetically sorted unique insults from the map into the vector.
	for (it = insultIndicesAndValues.begin(); it != insultIndicesAndValues.end(); it++) {
		returnInsults.push_back(it->second);
	}
	return returnInsults;
}

vector<string> InsultGenerator::generateAndSave(const string fileName, const int numInsults) {
	vector<string> returnInsults = generate(numInsults);

	ofstream outputFile(fileName.c_str());
	// Check that the file can be opened.
	if(outputFile.fail()) {
		throw FileException("Unable to open file: " + fileName + "\n");
	}
	// Save the insults to the file.
	for (unsigned int i = 0; i < returnInsults.size(); i ++) {
		outputFile << returnInsults[i] << endl;
	}
	outputFile.close();
	return returnInsults;
}

/*
 * Implementation of methods in the FileException class.
 */
FileException::FileException(const string& message) : message(message){}
string& FileException::what() {return message;}


/*
 * Implementation of methods in the NumInsultsOutOfBounds class.
 */
NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& message) : message(message){}
string& NumInsultsOutOfBounds::what() {return message;}
