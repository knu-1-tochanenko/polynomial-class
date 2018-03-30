#include"tpolynomial.h"

int main() {
	// Insert your code here
	// DELETE -->
	Polynomial first;

	first.add_monomial(0, 1.5);

	for (int i = 1; i < 5; i++)
		first.add_monomial(i, 0.8 + i * 1.2);

	first.print_polynomial();
	////////////////////////////////////////// <--
	PAUSE;
}
