#include <iostream>
using std::cout; using std::endl;
#include <sstream>
using std::ostringstream;
#include <string>
using std::string;

#include "polynomial.h"

//function takes in a fraction x and integer e
//returns x raised to e
Fraction fract_pow(Fraction x, int e) {
  if (e != 0) {
    Fraction new_x = x;

    for (int i = 0; i < e-1; i++) {
        new_x = new_x*x;
    }

    return new_x;

  } else {
    return Fraction(1);
  }
}

//takes in a vector cfs and constructs a polynomial
//polynomial coefs = cfs
Polynomial::Polynomial(const vector<Fraction>& cfs) {
  //helps us know when we've made it past leading zeroes
  bool afterLead = false;

  //reverse loop, insert values skip leading zeroes
  for (int i = cfs.size() - 1; i >= 0; i--) {
    if (cfs[i] != 0)
      afterLead = true;

    if (afterLead)
      coefs.insert(coefs.begin(), cfs[i]);
  }

  //if no vales were inserted place a zero in the coefs vector
  if (!coefs.size())
    coefs = {0};
}

//returns a printable string of the polynomial
string Polynomial::poly_to_string() const {
  ostringstream oss;

  //first check that the polynomial has more than one coef
  if (coefs.size() > 1) {
    //reverse loop
    for (int i = coefs.size() - 1; i >= 0; i--) {
      string coef = coefs[i].toString();

      //if the coef is a -1 set coef to "-"
      if (coefs[i] == Fraction(-1))
        coef = coef[0];

      //if the coef is a 1 set coef to ""
      if (coefs[i] == Fraction(1))
        coef = "";

      //adjust formating of trailing values
      if (i != coefs.size()-1) {
        if (coef[0] != '-') {
          coef = " + "+coef;
        }
        else  {
          coef.insert(1, " ");
          coef.insert(0, " ");
        }
      }

      if (coefs[i] != 0) {
        //add the coef string to oss
        oss << coef;
        if (i > 1) //add x to the power i
          oss << "x^" << i;
        else if (i == 1) //add x
          oss << "x";
      }
    }
  } else {
    //when the size is 1 convert the value and add to oss
    oss << coefs[0].toString();
  }

  //return a string of the oss
  return oss.str();
}

//returns the value of the polynomial using the provided value of x
Fraction Polynomial::evaluate(Fraction x) const {
  //initialize value to 0
  Fraction value(0);

  for (int i = coefs.size() - 1; i >= 0; i--) {

    //skip the constant
    if (i != 0) {
      //use fract_power to calculate the terms value
      value = value + (coefs[i] * fract_pow(x, i));
    } else {
      //add the constant
      value = value + coefs[i];
    }
  }
  return value;
}


//returns the derivative of the polynomial
Polynomial Polynomial::derivative() const{
  //initialize derivative vector
  vector<Fraction> deriv;

  //reverse loop through coefs
  for (int i = coefs.size() - 1; i >= 0; i--) {
    if (i != 0) //skip the constant, insert coef*i
      deriv.insert(deriv.begin(), coefs[i]*i);
  }

  return Polynomial(deriv);
}

//returns the indefinite integral of the polynomial
//assuming the constant of integration is 0
Polynomial Polynomial::integral() const {
  vector<Fraction> integral {0};

  for (int i = coefs.size() - 1; i >= 0; i--) {
      integral.insert(integral.begin()+1, coefs[i]*Fraction(1, i+1));
  }

  return Polynomial(integral);
}

//returns the value of the definite integral of
//the polynomial from lower to upper
Fraction Polynomial::integral(Fraction lower, Fraction upper) const {
  Polynomial indef_integral = this->integral();
  Fraction lower_val = indef_integral.evaluate(lower);
  Fraction upper_val = indef_integral.evaluate(upper);

  return upper_val-lower_val;
}
