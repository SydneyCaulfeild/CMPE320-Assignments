/*
 * ShapesGood.h
 *
 *      Author: Sydney Caulfeild
 *      Date: 11/29/2020
 *      This file contains the declarations for all classes used in assignment 5. The classes form a hierarchy, with Shape being the base class.
 */


#pragma once

#include <string>
using namespace std;

/* Shape class. This is a parent/ancestor class for all other classes in this file. */
class Shape {
public:
	Shape(const int length, const int width, const string borderColor);
	int getLength() const;
	int getWidth() const;
	virtual ~Shape() {};
	virtual void draw() = 0;
protected:
	virtual void drawBorder() = 0;
	string borderColour;
private:
	int length, width;
};

/* Fillable class is for any shapes that are filled with a colour. */
class Fillable {
public:
	Fillable(const string fillColour);
	virtual ~Fillable() {};	// destructors will automatically invoke parent destructor(s), hence they are not explicitly invoked.
protected:
	string fillColour;
	virtual void fill() = 0;
};

/* Labelled class is for shapes that have a text label. */
class Labelled {
public:
	Labelled(const string label);
	virtual ~Labelled() {};
protected:
	string label;
	virtual void drawText() = 0;
};

/* Square class. This class extends the Shape class. */
class Square : public Shape {
public:
	Square(const int length, const int width, const string borderColour);
	virtual void draw();
	virtual ~Square() {};
protected:
	virtual void drawBorder();
};

/* Class for a square that is filled in with a colour. This class extends both the Square and Fillable classes. */
class FilledSquare : public Square, Fillable {
public:
	FilledSquare(const int length, const int width, const string borderColour, const string fillColour);
	virtual void draw();
	virtual ~FilledSquare() {};
protected:
	virtual void fill();
};

/* Class for a square that is filled in with a colour and has a text label. This class extends teh FilledSquare and Labelled classes. */
class FilledTextSquare : public FilledSquare, Labelled {
public:
	FilledTextSquare(const int length, const int width, const string borderColour, const string fillColour, const string label);
	virtual void draw();
	virtual ~FilledTextSquare() {};
protected:
	virtual void drawText();
};

/* Circle class. This class extends the shape class. */
class Circle : public Shape {
public:
	Circle(const int length, const int width, const string borderColour);
	virtual void draw();
	virtual ~Circle() {};
protected:
	virtual void drawBorder();
};

/* Class for a circle that is filled in with a colour. This class extends both the Circle and Fillable classes. */
class FilledCircle : public Circle, Fillable {
public:
	FilledCircle(const int length, const int width, const string borderColour, const string fillColour);
	virtual void draw();
	virtual ~FilledCircle() {};
protected:
	virtual void fill();
};

/* Arc class. This class extends the shape class. */
class Arc : public Shape {
public:
	Arc(const int length, const int width, const string borderColour);
	virtual void draw();
	virtual ~Arc() {};
protected:
	virtual void drawBorder();
};
