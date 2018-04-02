#include "tpolynomial.h"

// Monomial structure functions
void Polynomial::Monomial::update(int exponent_value, double coefficient, Monomial* next) {
	this->exponent_value = exponent_value;
	this->coefficient = coefficient;
	this->next = next;
}

void Polynomial::Monomial::update(Monomial* next) {
	this->next = next;
}

void Polynomial::Monomial::update(double coefficient) {
	this->coefficient = coefficient;
}

// Private Polynomial functions
void Polynomial::print_element(Monomial* element) {
	if (element->next != NULL) {
		print_element(element->next);
		cout << element->exponent_value << "  :  " << element->coefficient << endl;;
	}
}

bool Polynomial::normalize_polynomial() {
	if (head_element == NULL) // If the list is empty
		return false;
	Monomial* cur_element = head_element;

	while (cur_element->next != NULL) {
		if (cur_element->next->coefficient == 0) {
			Monomial* backup_value = cur_element->next->next;
			delete backup_value->next;
			cur_element->next = backup_value;
		}
	}

	if (head_element->coefficient == 0) {
		// If the head element is the one element in the list
		Monomial* new_head = (head_element->next == NULL ? NULL : head_element->next);
		delete head_element;
		head_element = new_head;
	}

	return false;
}

void Polynomial::wipe(Monomial *element) {
	if (element != NULL)
		wipe(element->next);
	if (element == NULL)
		return;
	else {
		delete element;
	}
}

// Public Polynomial functions
Polynomial::Polynomial() {
	head_element = NULL;
}

Polynomial::Polynomial(int n_args, ...) {
	va_list v;
	va_start(v, n_args);
	double cur = va_arg(v, double);

	int number_of_iterations = 0;
	while (cur == 0) {					// Clear all null vars
		cur = va_arg(v, double);
		number_of_iterations++;
	}

	head_element = new Monomial;
	head_element->update(number_of_iterations, cur, NULL);
	Monomial* cur_element = head_element;

	while (number_of_iterations < n_args) {
		number_of_iterations++;
		cur = va_arg(v, double);
		if (cur == 0) {
			continue;
		}
		else {
			Monomial* new_element = new Monomial;
			new_element->update(number_of_iterations, cur, NULL);
			cur_element->update(new_element);
			cur_element = new_element;
		}
	}
}

bool Polynomial::delete_monomial(int exponent_value) {
	Monomial* cur_element = head_element;
	while ((cur_element != NULL) && (cur_element->exponent_value != exponent_value))
		cur_element = cur_element->next;
	if (cur_element == NULL)
		return false;
	else {
		cur_element->exponent_value = 0;
		return this->normalize_polynomial();
	}
}

void Polynomial::add_monomial(int exponent_value, double coefficient) {
	Monomial* cur_element = head_element;

	if (head_element == NULL) {
		head_element = new Monomial;
		head_element->update(exponent_value, coefficient, NULL);
		return;
	}

	while ((cur_element->next != NULL) && (cur_element->next->exponent_value < exponent_value))
		cur_element = cur_element->next;

	if (cur_element->exponent_value == exponent_value) {
		cur_element->update(cur_element->coefficient + coefficient);
		return;
	}

	if ((cur_element->next != NULL) && (cur_element->next->exponent_value == exponent_value)) {
		cur_element->next->update(cur_element->next->coefficient + coefficient);
		// Exit while trying to add an existing item
		return;
	}

	Monomial* new_element = new Monomial;

	new_element->exponent_value = exponent_value;
	new_element->coefficient = coefficient;

	if (exponent_value < head_element->exponent_value) {
		new_element->next = head_element;
		head_element = new_element;
	}
	else {
		new_element->next = cur_element->next;
		cur_element->next = new_element;
	}
}

void Polynomial::subtract_monomial(int exponent_value, double coefficient) {
	add_monomial(exponent_value, coefficient * (-1));
}

bool Polynomial::multiply_monomial(int exponent_value, double coefficient) {
	Monomial* cur_element = head_element;

	while ((cur_element != NULL) && (cur_element->exponent_value != exponent_value))
		cur_element->next;

	if (cur_element == NULL) {
		// There is no such element or the list is empty
		return false;
	}
	else {
		if (coefficient == 0)
			delete_monomial(exponent_value);
		else
			cur_element->coefficient *= coefficient;
	}
	return false;
}

bool Polynomial::divide_monomial(int exponent_value, double coefficient) {
	if (coefficient == 0) {
		throw "Division by zero condition!";
		return false;
	}
	else
		multiply_monomial(exponent_value, 1 / coefficient);
	return false;
}

void Polynomial::print_polynomial() {
	Monomial* cur_element = head_element;
	print_element(cur_element);
	cout << endl;
}

void Polynomial::copy_polynomial(Polynomial polynomial) {
	this->wipe(this->head_element);
	Monomial* second_element = polynomial.head_element;
	Monomial* new_monomial = new Monomial;
	Monomial* cur_element;
	new_monomial->update(second_element->exponent_value, second_element->coefficient, NULL);
	this->head_element = new_monomial;
	cur_element = this->head_element;

	while (second_element != NULL) {
		Monomial* new_element = new Monomial;
		cur_element->update(new_element);
		new_element->update(second_element->exponent_value, second_element->coefficient, NULL);
		second_element = second_element->next;
	}
}

void Polynomial::add_polynomials(Polynomial element) {
	Monomial* cur_element = element.head_element;
	while (cur_element->next != NULL) {
		add_monomial(cur_element->exponent_value, cur_element->coefficient);
		cur_element = cur_element->next;
	}
}

void Polynomial::subtract_polynomials(Polynomial element) {
	Monomial* cur_element = element.head_element;
	while (cur_element->next != NULL) {
		subtract_monomial(cur_element->exponent_value, cur_element->coefficient);
		cur_element = cur_element->next;
	}
}

void Polynomial::multiply(double number) {
	Monomial* cur_element = head_element;
	while (cur_element != NULL) {
		cur_element->coefficient *= number;
	}
}

bool Polynomial::divide(double number) {
	if (number == 0.0) {
		throw "Division by zero condition!";
		return false;
	}
	else
		multiply(1 / number);
	return true;
}

void Polynomial::multiply_polynomials(Polynomial second_polynomial) {
	// TODO second_polynomial
	
	Polynomial sub_polynomial;
	sub_polynomial.copy_polynomial(*this);
	Monomial* element_to_multiply = second_polynomial.head_element;

	if (second_polynomial.head_element == NULL ||
		(second_polynomial.head_element->next == NULL && second_polynomial.head_element->coefficient == 0)) {
		wipe(head_element);
	}

	while (element_to_multiply != NULL) {
		Monomial* first_element = head_element;
		while (first_element != NULL) {
			sub_polynomial.add_monomial(first_element->exponent_value + element_to_multiply->exponent_value,
				first_element->coefficient * element_to_multiply->coefficient);
			first_element = first_element->next;
		}
		element_to_multiply = element_to_multiply->next;
	}

	delete this;
	this = &sub_polynomial;
}

// Divides current polynomial by second one and returns remainder
Polynomial Polynomial::divide_polynomials(Polynomial element) {
	// TODO divide_polynomials
}
