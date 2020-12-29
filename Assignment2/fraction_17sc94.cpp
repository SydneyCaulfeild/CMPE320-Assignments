/*
 * fraction_17sc94.cpp
 *
 *      Author: Sydney Caulfeild
 *      Date: 10/16/2020
 *      This file implements all classes and non-member functions used in assignment 2. The following classes are implemented:
 *      Fraction Class - a class to represent a fraction using integer numerators and denominators.
 *      FractionException Class - an exception class used to throw exceptions relating to illegal fractions (i.e. divide by zero).
 *      This file also implements the non-member functions that are used to override other operators.
 *      The following unary operators are overridden for the fraction class: - (negation), ++ (pre-increment), and ++ (post-increment).
 *      The following binary operators are overridden for the fraction class: +, -, *, /, +=, <, <=, ==, !=, >=, >, <<, >>.
 */

#include "fraction_17sc94.h"

#include <iostream>
#include <string>

using namespace std;

/*+	Initialize a fraction to 0/1 when no parameters are provided.	-*/
Fraction::Fraction() : num(0), den(1) {}

/*+ Initialize a fraction to numerator/1 when only a numerator is provided.	-*/
Fraction::Fraction(int numerator) : num(numerator), den(1) {}

/*+ Initialize a fraction with both the numerator and denominator provided as parameters.	-*/
Fraction::Fraction(int numerator, int denominator) {
	if (denominator == 0){
		throw FractionException("You cannot divide a number by zero.\n");
	}
	int gcd = calculateGcd(numerator, denominator);
	numerator = numerator/gcd;
	denominator = denominator/gcd;

	// If both are negative, negate both to make them positive.
	if (numerator < 0 && denominator < 0){
		num = -numerator;
		den = -denominator;
	}
	// If only the denominator is negative, negate both so that only the numerator is negative.
	else if (denominator < 0){
		num = -numerator;
		den = -denominator;
	}
	// Otherwise, keep them as they are.
	else {
		num = numerator;
		den = denominator;
	}
}

/*+ Numerator accessor. -*/
int Fraction::numerator() const {
	return num;
}

/*+ Denominator accessor. -*/
int Fraction::denominator() const {
	return den;
}

/*+	Negation operator.	-*/
Fraction Fraction:: operator-() {
	return Fraction(-this->numerator(), this->denominator());
}

/*+ Pre-increment operator. -*/
Fraction& Fraction:: operator++() {
	num += den;
	return *this;
}

/*+ Post-increment operator. -*/
Fraction Fraction:: operator++(int unused) {
	Fraction clone(num, den);
	num += den;
	return clone;
}

/*+ Addition and assignment operator -*/
Fraction& Fraction:: operator+=(const Fraction& right) {
	int rnum = right.numerator();
	int rden = right.denominator();
	// If the denominators are not equal, multiply each fraction by the other's denominator.
	if (den != rden) {
		int temp = den;
		num *= rden;
		den *= rden;
		rnum *= temp;
		rden *= temp;
	}
	num = num + rnum;
	// Use the greatest common divisor to reduce the addition result to it's normalized state.
	int gcd = calculateGcd(num, den);
	num = num/gcd;
	den = den/gcd;
	return *this;
}

/*+ Constructor and what() function for the FractionException class. -*/
FractionException::FractionException(const string& message) : message(message){}
string& FractionException::what() {return message;}

/*+ A helper function to calculate the greatest common divisor. -*/
int calculateGcd(const int n, const int d) {
	if (d == 0) {
		return n;
	}
	return calculateGcd(d, n % d);
}

/*+ A helper function to calculate the lowest common multiple. This function relies on the calculateGcd() function. -*/
int calculateLcm (const int lden, const int rden) {
	return (lden*rden) / calculateGcd(lden, rden);
}

/*+ The addition operator. -*/
Fraction operator+(const Fraction& left, const Fraction& right) {
	// If the denominators are not equal, use the lowest common multiple to make them equal.
	if (left.denominator() != right.denominator()) {
		int lcm = calculateLcm(left.denominator(), right.denominator());
		int lMult = lcm/left.denominator();
		int rMult = lcm/right.denominator();
		return Fraction(left.numerator()*lMult + right.numerator()*rMult, left.denominator()*lMult);
	}
	else {
		return Fraction(left.numerator() + right.numerator(), left.denominator());
	}
}

/*+ The subtraction operator. -*/
Fraction operator-(const Fraction& left, const Fraction& right) {
	// If the denominators are not equal, use the lowest common multiple to make them equal.
	if (left.denominator() != right.denominator()) {
		int lcm = calculateLcm(left.denominator(), right.denominator());
		int lMult = lcm/left.denominator();
		int rMult = lcm/right.denominator();
		return Fraction(left.numerator()*lMult - right.numerator()*rMult, left.denominator()*lMult);
	}
	else {
		return Fraction(left.numerator() - right.numerator(), left.denominator());
	}
}
/*+ The multiplication operator. -*/
Fraction operator*(const Fraction& left, const Fraction& right) {
	return Fraction (left.numerator()*right.numerator(), left.denominator()*right.denominator());
}

/*+ The division operator. -*/
Fraction operator/(const Fraction& left, const Fraction& right) {
	return Fraction (left.numerator()*right.denominator(), left.denominator()*right.numerator());
}

/*+ The equal-to operator. -*/
bool operator==(const Fraction& left, const Fraction& right) {
	return (left.numerator()==right.numerator() && left.denominator()==right.denominator());
}

/*+ The not equal-to operator. -*/
bool operator!=(const Fraction& left, const Fraction& right) {
	return (left.numerator()!=right.numerator() || left.denominator()!=right.denominator());
}

/*+ The less-than operator. -*/
bool operator<(const Fraction& left, const Fraction& right) {
	int lnum = left.numerator();
	int rnum = right.numerator();
	// If the denominators are not equal, use the lowest common multiple to make them equal so that the numerators can be compared.
	if (left.denominator() != right.denominator()) {
		int lcm = calculateLcm(left.denominator(), right.denominator());
		int lMult = lcm/left.denominator();
		int rMult = lcm/right.denominator();
		lnum = left.numerator()*lMult;
		rnum = right.numerator()*rMult;
	}
	return (lnum < rnum);
}

/*+ The greater-than operator. -*/
bool operator>(const Fraction& left, const Fraction& right) {
	int lnum = left.numerator();
	int rnum = right.numerator();
	// If the denominators are not equal, use the lowest common multiple to make them equal so that the numerators can be compared.
	if (left.denominator() != right.denominator()) {
		int lcm = calculateLcm(left.denominator(), right.denominator());
		int lMult = lcm/left.denominator();
		int rMult = lcm/right.denominator();
		lnum = left.numerator()*lMult;
		rnum = right.numerator()*rMult;
	}
	return (lnum > rnum);
}

/*+ The less-than or equal-to operator. This function uses the less-than operator function.	-*/
bool operator<=(const Fraction& left, const Fraction& right) {
	return (operator<(left, right) || left==right);
}

/*+ The greater-than or equal-to operator. This function uses the greater-than operator function.	-*/
bool operator>=(const Fraction& left, const Fraction& right) {
	return (operator>(left, right) || left==right);
}

/*+ The << operator used for cout. -*/
ostream& operator<<(ostream& out, const Fraction& frac) {
	out << frac.numerator() << "/" << frac.denominator();
	return out;
}

/*+ The >> operator used for cin. -*/
istream& operator>>(istream& in, Fraction& frac) {
	int numer;
	int denom=1;
	int peekchar;
	bool valid=false;

	    in >> numer;
	    peekchar = in.peek();
	    if(in && peekchar == '\n') {
	        valid = true;
	    }
	    if(in && peekchar == '/') {
	        in.get();
	        in >> denom;
	        valid = true;
	    }
	    if (in && valid) {
	        frac = Fraction(numer, denom);
	     }
	    else {
	    	throw FractionException("That is not a valid fraction.");
	    }
	     return in;
}

