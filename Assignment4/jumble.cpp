/*
 * jumble.h
 *
 *      Author: Sydney Caulfeild
 *      Date: 11/8/2020
 *      This file contains the implementations for all classes used in assignment 4. The following classes are implemented:
 *      JumblePuzzle Class - Used to create a word search with a hidden word using a 2D array stored on the heap.
 *      BadJumbleException Class - an exception class used to display errors when user input is invalid or the word search can't be initialized.
 */

#include "jumble.h"

#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <string>

using namespace std;

JumblePuzzle::JumblePuzzle() {
	jumble = NULL;
	rowPos = 0;
	colPos = 0;
	size = 0;
	direction = 0;
}

JumblePuzzle::JumblePuzzle(const string& wordToHide, const string& difficulty) {
	size = wordToHide.length();
	// Check that the user input satisfies the word size conditions.
	if (size < 3) {
		throw BadJumbleException("Your word is too short. It must be between 3 and 10 letters long.");
	}
	else if (size > 10) {
		throw BadJumbleException("Your word is too long. It must be between 3 and 10 letters long.");
	}

	// Check that the user provided a valid difficulty level. Single letters are accepted.
	char firstLetter = difficulty.at(0);
	if (difficulty == "easy" || (difficulty.length() == 1 && firstLetter == 'e') || (difficulty.length() == 1 && firstLetter == 'E')) {
		size = size * 2;
	}
	else if (difficulty == "medium" || (difficulty.length() == 1 && firstLetter == 'm') || (difficulty.length() == 1 && firstLetter == 'M')) {
		size = size * 3;
	}
	else if (difficulty == "hard" || (difficulty.length() == 1 && firstLetter == 'h') || (difficulty.length() == 1 && firstLetter == 'H')){
		size = size * 4;
	}
	else {
		throw BadJumbleException("You did not provide a correct difficulty level. Example input for easy: \"easy\" or \"e\" or \"E\".");
	}
	// Initialize time seed.
	srand((unsigned)time(NULL));

	// Create 2d array on the heap for the puzzle.
	jumble = new char*[size];
	for (int i = 0; i < size; i++) {
		jumble[i] = new char[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			jumble[i][j] = 'a' + rand()%26;;
		}
	}

	// Generate random row and column positions for the first letter of the word.
	rowPos = rand() % size;
	colPos = rand() % size;

	// Set the first letter in the puzzle.
	jumble[rowPos][colPos] = wordToHide.at(0);

	// Initialize directions and choose one.
	const char* directions = "nesw";
	direction = directions[rand() % 4];

	// If the direction is not valid, choose the opposite direction as this is guaranteed to work.
	int numLetters = (int) wordToHide.length() - 1;
	if (rowPos + numLetters >= size && direction == 's') {
		direction = 'n';
	}
	else if (colPos + numLetters >= size && direction == 'e') {
		direction = 'w';
	}
	else if (rowPos - numLetters < 0 && direction == 'n') {
		direction = 's';
	}
	else if (colPos - numLetters < 0 && direction == 'w') {
		direction = 'e';
	}

	jumble = JumblePuzzle::createWordSearch(wordToHide, size, direction, rowPos, colPos);
}

// Copy constructor that makes a new 2D array to prevent aliasing.
JumblePuzzle::JumblePuzzle(const JumblePuzzle& jp) {
	size = jp.getSize();
	rowPos = jp.getRowPos();
	colPos = jp.getColPos();
	direction = jp.getDirection();

	jumble = new char*[size];

	for (int i = 0; i < size; i++) {
		jumble[i] = new char[size];
	}

	charArrayPtr* tempJumble = jp.getJumble();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			jumble[i][j] = tempJumble[i][j];
		}
	}
}


JumblePuzzle::~JumblePuzzle() {
	// Delete a 2D array.
	for(int i = 0; i < size; i++) {
		delete jumble[i];
		jumble[i] = nullptr;
	}
	delete jumble;
	jumble = nullptr;
}

// Overloaded assignment operator that also creates a new 2D array to prevent aliasing.
JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& jp){
	if (this != &jp) {
		for (int i = size - 1; i >= 0; i--) {
			delete[] jumble[i];
		}
		delete[] jumble;

	rowPos= jp.getRowPos();
	colPos = jp.getColPos();
	direction = jp.getDirection();
	size = jp.getSize();

	if (jp.getJumble()) {
		jumble = new char* [size];
		for (int i = 0; i < size; i++) {
			jumble[i] = new char[size];
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				jumble[i][j] = jp.getJumble()[i][j];
			}
		}
	}
	}
	return *this;
}

charArrayPtr* JumblePuzzle::getJumble() const {
	// Return a new copy of the array to prevent aliasing.
	charArrayPtr* newJumble = new char* [size];

	for (int i = 0; i < size; i++) {
		newJumble[i] = new char[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			newJumble[i][j] = jumble[i][j];
		}
	}

	return newJumble;
}

int JumblePuzzle::getSize() const {
	return size;
}

int JumblePuzzle::getRowPos() const {
	return rowPos;
}

int JumblePuzzle::getColPos() const {
	return colPos;
}

char JumblePuzzle::getDirection() const {
	return direction;
}

BadJumbleException::BadJumbleException(const string& e)
{
	message = e;
}

string& BadJumbleException::what()
{
	return message;
}

charArrayPtr* JumblePuzzle::createWordSearch(const string& wordToHide, int size, char direction, int rowPos, int colPos) {


  charArrayPtr* jumble = new char*[size];

  int cornerRowPos;
  int cornerColPos;

  int increment;
  int currentWordIndex;

  // If the direction is south or east, start by inserting the beginning of the word.
  if (direction == 's' || direction == 'e') {
      cornerRowPos = rowPos;
      cornerColPos = colPos;
      currentWordIndex = 0;
      increment = 1;
  }
  // Otherwise, if the direction is west or north, start by inserting the end of the word and work backwards.
  else if (direction == 'w') {
      cornerRowPos = rowPos;
      cornerColPos = colPos - (wordToHide.length() - 1);
      currentWordIndex = wordToHide.length() - 1;
      increment = -1;
  }
  else if (direction == 'n') {
      cornerRowPos = rowPos - (wordToHide.length() - 1);
      cornerColPos = colPos;
      currentWordIndex = wordToHide.length() - 1;
      increment = -1;
  }
  bool directionIsVertical = false;
  if (direction == 'n' || direction == 's') {
	  directionIsVertical = true;
  }
  // Variable to indicate whether the current row and column position should be for the wordToHide (true) or a random letter (false).
  bool insertWord = false;
  // Iterate through the array.
  for (int row = 0; row < size; row++) {
      jumble[row] = new char[size];
      for (int col = 0; col < size; col++) {
    	  // If this position matches the row and col for the wordToHide, indicate that the word should be inserted.
          if (row == cornerRowPos && col == cornerColPos) {
              insertWord = true;
          }

          // Determine which direction to move in.
          bool moveHorizontal = false;
          if (!directionIsVertical && row == cornerRowPos) {
        	  moveHorizontal = true;
          }
          bool moveVertical = false;
          if (directionIsVertical && col == cornerColPos) {
        	  moveVertical = true;
          }

          // Insert the wordToHide.
          if (insertWord && (moveHorizontal || moveVertical)) {
              jumble[row][col] = wordToHide[currentWordIndex];
              currentWordIndex += increment;
              // Check if the entire word has been completed. Since this can be done going forwards or backwards, must check if the currentWordInde is negative or has reached the end of the word.
              if (currentWordIndex < 0 || currentWordIndex == wordToHide.length()) {
                  insertWord = false;
              }
          }
          // If this position is not meant for part of the word to hide, insert a random letter.
          else {
              char randomLetter = rand() % 26 + 'a';
              jumble[row][col] = randomLetter;
          }
      }
  }
  return jumble;
}
