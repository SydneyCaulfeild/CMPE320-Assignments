/*
 * fraction_17sc94.h
 *
 *      Author: Sydney Caulfeild
 *      Date: 10/16/2020
 *      This file contains the declarations for all classes used in assignment 2. The following classes are declared:
 *      Fraction Class - a class to represent a fraction using integer numerators and denominators.
 *      FractionException Class - an exception class used to throw exceptions relating to illegal fractions (i.e. divide by zero).
 *      This file also contains the declarations for non-member functions that are used to override other operators.
 *      The following unary operators are overridden for the fraction class: - (negation), ++ (pre-increment), and ++ (post-increment).
 *      The following binary operators are overridden for the fraction class: +, -, *, /, +=, <, <=, ==, !=, >=, >, <<, >>.
 */

#pragma once

#include <string>

using namespace std;

class Fraction {
public:
	Fraction();							// Initializes a fraction as 0/1.
	Fraction(int n);					// Sets the numerator to the integer provided and the denominator to 1.
	Fraction(int n, int d);				// Sets the numerator to the first integer parameter and the denominator to the second.

	int numerator() const;				// Numerator accessor.
	int denominator() const;			// Denominator accessor.

	Fraction operator-();
	Fraction& operator++();				// Pre-increment.
	Fraction operator++(int unused);	// Post-increment.
	Fraction& operator+=(const Fraction& right);

private:
	int num;							// Numerator variable.
	int den;							// Denominator variable.
};

class FractionException {
public:
	FractionException(const string& message);
	string& what();
private:
	string message;
};

// Function to calculate the greatest common divisor between a numerator and a denominator.
int calculateGcd(const int n, const int d);
// Function to calculate the lowest common multiple between two fraction denominators.
int calculateLcm (const int lden, const int rden);

// Non-member overridden operator functions for the fraction class.
Fraction operator+(const Fraction& left, const Fraction& right);
	Fraction operator-(const Fraction& left, const Fraction& right);
	Fraction operator*(const Fraction& left, const Fraction& right);
	Fraction operator/(const Fraction& left, const Fraction& right);
	bool operator==(const Fraction& left, const Fraction& right);
	bool operator!=(const Fraction& left, const Fraction& right);
	bool operator<(const Fraction& left, const Fraction& right);
	bool operator>(const Fraction& left, const Fraction& right);
	bool operator<=(const Fraction& left, const Fraction& right);
	bool operator>=(const Fraction& left, const Fraction& right);
	ostream& operator<<(ostream& out, const Fraction& frac);
	istream& operator>>(istream& in, Fraction&frac);

