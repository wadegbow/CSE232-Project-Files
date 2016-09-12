#ifndef POLYGON
#define POLYGON

#include<iostream>
using std::ostream;
#include<vector>
using std::vector;
#include<string>
using std::string;

#include "point.h"

class RegularPolygon{
private:
    long n_;
    Point p_;
    double s_;
    double a_;
    double r_;

public:
    // constructor
    RegularPolygon(long, Point);

    // getters
    double get_a();
    double get_r();
    double get_s();
    long get_n();

    // setters
    void set_a(double);
    void set_r(double);
    void set_s(double);

    double get_area();
    void add(double,char);
    void mult(double,char);

    vector<Point> generate_points();

    friend ostream& operator<<(ostream&, RegularPolygon&);
};

string vector_to_string(vector<Point>&);

#endif
