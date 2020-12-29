/*
 * jumble.h
 *
 *      Author: Sydney Caulfeild
 *      Date: 11/8/2020
 *      This file contains the declarations for all classes used in assignment 4. The following classes are declared:
 *      JumblePuzzle Class - Used to create a word search with a hidden word using a 2D array stored on the heap.
 *      BadJumbleException Class - an exception class used to display errors when user input is invalid or the word search can't be initialized.
 */

#pragma once

#include <string>

using namespace std;

typedef char* charArrayPtr;

class JumblePuzzle {
public:
	/* Default constructor. */
	JumblePuzzle();
	/* Constructor to create a puzzle with wordToHide hidden in it and with a specified difficulty of easy, medium, or hard. */
	JumblePuzzle(const string& wordToHide, const string& difficulty);
	/* Copy constructor. */
	JumblePuzzle(const JumblePuzzle& jp);
	/* Destructor. */
	~JumblePuzzle();
	/* Overload of assignment operator. */
	JumblePuzzle& operator=(const JumblePuzzle& jp);

	/* Accessors. */
	charArrayPtr* getJumble() const;
	int getSize() const;
	int getRowPos() const;
	int getColPos() const;
	char getDirection() const;

private:
	/* Private attributes. */
	int size;
	charArrayPtr* jumble;
	int rowPos;
	int colPos;
	char direction;

	/* Helper method for the constructor to create a word search. */
	static charArrayPtr* createWordSearch(const string& hiddenWord, int puzzleSize, char direction, int rowPos, int colPos);

};

/* Exception class used for invalid user input or if the puzzle can't be initialized. */
class BadJumbleException {
public:
	BadJumbleException(const string& message);
	string& what();
private:
	string message;
};
