/*
 * This file contains some truly ugly code.  The creation and population of the
 * vector<Shape*> collection of drawing shapes is OK, but the use of this collection
 * is incredibly awful.  Because polymorphism was not a consideration when the hierarchy
 * was constructed any code that attempts to draw a Shape must first determine what kind
 * of Shape object it has and then must invoke only the relevant drawing functions for
 * that shape.  Yuk!  And this hierarchy of Shapes is only partially populated - imagine
 * how much worse this code would be if you actually had objects for all possible shapes -
 * outlines only, filled and not filled, and with and without text!
 *
 * For CISC/CMPE 320, Assignment 5
 */
#include <iostream>
#include <string>
#include <vector>

#include "ShapesBad.h"

using namespace std;
/*
int main() {

	int count(0);
	vector<Shape*> shapes;
	shapes.push_back(new Square(10, 10));
	shapes.push_back(new FilledSquare(10, 10));
	shapes.push_back(new FilledTextSquare(10, 10));
	shapes.push_back(new Circle(10, 10));
	shapes.push_back(new FilledCircle(10, 10));
	shapes.push_back(new Arc(10, 10));

	for (Shape* shp : shapes) {
		cout << "\nShape " << count++ << ":";
		if (Square* s = dynamic_cast<Square*>(shp)) {
			s->drawOutside("orange");
		} else if (FilledSquare* s = dynamic_cast<FilledSquare*>(shp)) {
			s->drawOutside("purple");
			s->fill("red");
		} else if (FilledTextSquare* s = dynamic_cast<FilledTextSquare*>(shp)) {
			s->drawOutside("green");
			s->fill("gray");
			s->drawText("Hello!");
		} else if (Circle* s = dynamic_cast<Circle*>(shp)) {
			s->drawOutside("blue");
		} else if (FilledCircle* s = dynamic_cast<FilledCircle*>(shp)) {
			s->drawOutside("yellow");
			s->fill("green");
		} else if (Arc* s = dynamic_cast<Arc*>(shp))
			s->draw("puce");
	} // end for

	for (Shape* shp : shapes)
		delete shp;

} // end main

/*
CONSOLE OUTPUT:

Shape 0:
Drawing a orange square.
Shape 1:
Drawing a purple square. With red fill.
Shape 2:
Drawing a green square. With gray fill. Containing the text: "Hello!".
Shape 3:
Drawing a blue circle.
Shape 4:
Drawing a yellow circle. With green fill.
Shape 5:
Drawing a puce arc.
*/
