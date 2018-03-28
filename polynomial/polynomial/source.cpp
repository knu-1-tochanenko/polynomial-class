/*
PosSiblY wOrkInG AddItIon anD SubStrActiOn oF tWo
pOlyNomIal exPrEssIonS
Weird code was written by
VLADISLAV TOCHANENKO
28.03.2018
*/

#include <iostream>
#include <stdarg.h>

using namespace std;

#define PAUSE (system("pause"))

class Polynomial {
private:
	struct Monomial {
		int x;
		double a;
		Monomial* next;

		void update(int x, double a, Monomial* next) {
			this->x = x;
			this->a = a;
			this->next = next;
		}

		void update(Monomial* next) {
			this->next = next;
		}

		void update(double a) {
			this->a = a;
		}

	};

	Monomial* head_element;

	void print_element(Monomial* element) {
		if (element->next != NULL) {
			print_element(element->next);
			cout << element->x << "  :  " << element->a << endl;;
		}
	}

public:
	Polynomial() {
		head_element = NULL;
	}

	Polynomial(int n_args, ...) {
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

	void add(int x, double a) {
		Monomial* cur_element = head_element;
		while ((cur_element->next != NULL) && (cur_element->next->x < x))
			cur_element = cur_element->next;

		if (cur_element->x == x) {						// Shit
			cur_element->update(a + cur_element->a);	// Shit
			return;										// Shit
		}

		if ((cur_element->next != NULL) && (cur_element->next->x == x)) {
			cur_element->next->update(a + cur_element->next->a);
			return;						// Exit while trying to add 
		}

		Monomial* new_element = new Monomial;

		new_element->x = x;
		new_element->a = a;

		if (x < head_element->x) {
			new_element->next = head_element;
			head_element = new_element;
		}
		else {
			new_element->next = cur_element->next;
			cur_element->next = new_element;
		}
	}

	// TODO : Merge SUB and ADD functions
	void sub(int x, double a) {
		Monomial* cur_element = head_element;
		while ((cur_element->next != NULL) && (cur_element->next->x < x))
			cur_element = cur_element->next;

		if (cur_element->x == x) {						// Shit
			cur_element->update(a - cur_element->a);	// Shit
			return;										// Shit
		}

		if ((cur_element->next != NULL) && (cur_element->next->x == x)) {
			cur_element->next->update(a - cur_element->next->a);
			return;						// Exit while trying to add 
		}

		Monomial* new_element = new Monomial;

		new_element->x = x;
		new_element->a = -a;

		if (x < head_element->x) {
			new_element->next = head_element;
			head_element = new_element;
		}
		else {
			new_element->next = cur_element->next;
			cur_element->next = new_element;
		}
	}

	void print() {
		Monomial* cur_element = head_element;

		print_element(cur_element);

		cout << endl;
	}

	Polynomial add_polynomial(Polynomial element) {

		Polynomial res;


	}

	void add_to(Polynomial element) {
		Monomial* cur_element = element.head_element;
		while (cur_element->next != NULL) {
			add(cur_element->x, cur_element->a);
			cur_element = cur_element->next;
		}
	}

	void sub_from(Polynomial element) {
		Monomial* cur_element = element.head_element;
		while (cur_element->next != NULL) {
			sub(cur_element->x, cur_element->a);
			cur_element = cur_element->next;
		}
	}

};

int main() {
	Polynomial first(10, 4.3, 0.0, 1.0, 6.0, 9.1, 0.0, 8.0, 1.11, 3.14, 0.0);
	Polynomial second(5, 1.1, 8.98, 0.0, 0.0, 2.0);

	first.print();
	second.print();

	first.add(0, 4.3);
	first.print();

	first.sub_from(second);
	first.print();

	PAUSE;
}