/*
 * ShapesGood.cpp
 *
 *      Author: Sydney Caulfeild
 *      Date: 11/29/2020
 *      This file contains the implementations for all classes used in assignment 5.
 */

#include <iostream>
#include <string>
#include "ShapesGood.h"

/* Implementation of the Shape class. */
Shape::Shape(const int length, const int width, const string borderColour) {
	this->length = length;
	this->width = width;
	this->borderColour = borderColour;
}

int Shape::getLength() const {
	return length;
}

int Shape::getWidth() const {
	return width;
}

/* Implementation of the Fillable class. */
Fillable::Fillable(const string fillColour) : fillColour(fillColour) {}

/* Implementation of the Labelled class. */
Labelled::Labelled(const string label) : label(label) {}

/* Implementation of the Square class. */
Square::Square(const int length, const int width, const string borderColour) : Shape(length, width, borderColour) {}

void Square::draw() {
	drawBorder();
}

void Square::drawBorder() {
	cout << "\nDrawing a " + borderColour + " square.";
}

/* Implementation of the FilledSquare class. */
FilledSquare::FilledSquare(const int length, const int width, const string borderColour, const string fillColour) : Square(length, width, borderColour), Fillable(fillColour) {}

void FilledSquare::draw() {
	drawBorder();
	fill();
}

void FilledSquare::fill() {
	cout << " With " + fillColour + " fill.";
}

/* Implementation of the FilledTextSquare class. */
FilledTextSquare::FilledTextSquare(const int length, const int width, const string borderColour, const string fillColour, const string label) : FilledSquare(length, width, borderColour, fillColour), Labelled(label) {}

void FilledTextSquare::draw() {
	drawBorder();
	fill();
	drawText();
}

void FilledTextSquare::drawText() {
	cout << " Containing the text: \"" << label << "\".";
}

/* Implementation of the Circle class. */
Circle::Circle(const int length, const int width, const string borderColour) : Shape(length, width, borderColour) {}

void Circle::draw() {
	drawBorder();
}

void Circle::drawBorder() {
	cout << "\nDrawing a " + borderColour + " circle.";
}

/* Implementation of the FilledCircle class. */
FilledCircle::FilledCircle(const int length, const int width, const string borderColour, const string fillColour) : Circle(length, width, borderColour), Fillable(fillColour) {}

void FilledCircle::draw() {
	drawBorder();
	fill();
}

void FilledCircle::fill() {
	cout << " With " + fillColour + " fill.";
}

/* Implementation of the Arc class. */
Arc::Arc(const int length, const int width, const string borderColour) : Shape(length, width, borderColour) {}

void Arc::draw() {
	drawBorder();
}

void Arc::drawBorder() {
	cout << "\nDrawing a " + borderColour + " arc.";
}

