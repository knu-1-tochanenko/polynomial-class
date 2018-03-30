# University Project : polynomial-class

A class for processing polynomial expressions.

There are plenty of features:
- Special structure for monomials
- A list structure of monomials in polynomial
- Initialisation of polynomial using varargs
- All basic mathematical functions for monomials and polynomial
- The programm uses very little amount of space on RAM

### List of functions

##### Constructiors
- **Polynomial**();
- **Polynomial**(int n_args, ...);

#### Functions to work with monomials
- bool **delete_monomial**(int exponent_value)
  - Returns false if there is no monomial with current exponent_value
- void **add_monomial**(int exponent_value, double coefficient)
- void **subtract_monomial**(int exponent_value, double coefficient)
- bool **multiply_monomial**(int exponent_value, double coefficient)
  - Returns false if there is no monomial with current exponent_value
- bool **divide_monomial**(int exponent_value, double coefficient)
  - Returns false if there is no monomial with current exponent_value || coefficient == 0

#### Printing functions
- void **print_polynomial**()

#### Functions to work with polynomials
- void **add_polynomials**(Polynomial element)
- void **subtract_polynomials**(Polynomial element)
- void **multiply**(double number)
- bool **divide**(double number)
  - Returns false if number == 0
- void **multiply_polynomials**(Polynomial element)
- Polynomial **divide_polynomials**(Polynomial element)
  - Returns remainder, writes result into current polynomial
