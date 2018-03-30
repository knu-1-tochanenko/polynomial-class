#pragma once

//////////////////////////////////////////////////////////
//		A class for processing polynomial expressions.	//
//		Author : VLADISLAV TOCHANENKO					//
//		Creation date : 28.03.2018						//
//////////////////////////////////////////////////////////

#include <iostream>
#include <stdarg.h>

using namespace std;

#define PAUSE (system("pause"))

class Polynomial {
private:
	struct Monomial {
		int exponent_value;
		double coefficient;
		Monomial* next;

		// Functions which used to update current element
		void update(int exponent_value, double coefficient, Monomial* next);
		void update(Monomial* next);
		void update(double coefficient);
	};

	Monomial* head_element;

	// Prints all elements from the end of list
	void print_element(Monomial* element);
	bool normalize_polynomial();
	void wipe(Monomial *element);

public:
	Polynomial();
	Polynomial(int n_args, ...);

	bool delete_monomial(int exponent_value);
	void add_monomial(int exponent_value, double coefficient);
	void subtract_monomial(int exponent_value, double coefficient);
	bool multiply_monomial(int exponent_value, double coefficient);
	bool divide_monomial(int exponent_value, double coefficient);

	void print_polynomial();

	// Mathematical operations
	void add_polynomials(Polynomial element);
	void subtract_polynomials(Polynomial element);
	void multiply(double number);
	bool divide(double number);
	void multiply_polynomials(Polynomial element);
	Polynomial divide_polynomials(Polynomial element);

};
