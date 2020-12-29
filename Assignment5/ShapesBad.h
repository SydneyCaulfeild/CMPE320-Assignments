/*
 * This hierarchy is part of a structure supposedly to be used with a drawing program.  For
 * this assignment you are concerned with the structure and not about actually drawing
 * anything.  For the purpose of having a few attributes around, a Shape will have a size
 * and colours will be supplied when the Shape is to be drawn.  A Shape can have an outline
 * colour, a fill colour and could hold text.
 *
 * This is an example of a poor inheritance structure.  It has a single base class, Shape,
 * and all other classes extend Shape.  It is an example of an exponential hierarchy, since
 * all classes extend just the one base class and very little is shared.  As you will see
 * from the ugly code in TestBadShapes.cpp, this structure does not support polymorphism.
 *
 * For CISC/CMPE 320, Assignment 5
 */
/*
#pragma once

#include <string>
using namespace std;

class Shape {
public:
	Shape();
	Shape(int, int);
	virtual ~Shape();
	int getLength();
	int getWidth();
private:
	int length, width;
};

class Square : public Shape {
public:
	Square(int, int);
	void drawOutside(string);
};

class FilledSquare : public Shape {
public:
	FilledSquare(int, int);
	void drawOutside(string);
	void fill(string);
};

class FilledTextSquare : public Shape {
public:
	FilledTextSquare(int, int);
	void drawOutside(string);
	void fill(string);
	void drawText(string);
};

class Circle : public Shape {
public:
	Circle(int, int);
	void drawOutside(string);
};

class FilledCircle : public Shape {
public:
	FilledCircle(int, int);
	void drawOutside(string);
	void fill(string);
};

class Arc : public Shape {
public:
	Arc(int, int);
	void draw(string);
};
*/
