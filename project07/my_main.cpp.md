#include "polynomial.h"
#include "fraction.h"

#include <iostream>
using std::cout;
using std::endl;

int main() {
    vector<Fraction> test = {};
    Polynomial p1({6, Fraction(3, 2)}), p2({0, -2, 3, 0, 0, -4, 0, 0}),
    p3({0});

    cout << "p1 as string: " << p1.poly_to_string() << endl;
    cout << "p2 as string: " << p2.poly_to_string() << endl;
    cout << "p3 as string: " << p3.poly_to_string() << endl << endl;

    cout << "p1(1/2): " << p1.evaluate(Fraction(1, 2)) << endl << endl;
    cout << "p2(1/2): " << p2.evaluate(Fraction(1, 2)) << endl << endl;

    auto deriv_p1 = p1.derivative();
    cout << "p1.derivative(): " << deriv_p1.poly_to_string() << endl;
    auto deriv_p2 = p2.derivative();
    cout << "p2.derivative(): " << deriv_p2.poly_to_string() << endl<<endl;

    auto indef_integral_p1 = p1.integral();
    cout << "p1.integral(): " << indef_integral_p1.poly_to_string() << endl;
    auto indef_integral_p2 = p2.integral();
    cout << "p2.integral(): " << indef_integral_p2.poly_to_string() << endl<<endl;

    //cout << "p1(3/4): " << p1.evaluate(Fraction(3, 4)) << endl << endl;
    //cout << "p1(7/2): " << p1.evaluate(Fraction(7, 2)) << endl << endl;

    auto def_integral = p1.integral(Fraction(3, 4), Fraction(7, 2));
    cout << "p1.integral(3/4, 7/2): " << def_integral << endl << endl;
}
