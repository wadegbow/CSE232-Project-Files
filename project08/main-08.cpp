#include<iostream>
using std::cout; using std::endl;
#include<iomanip>
using std::setprecision;
#include<iterator>
using std::ostream_iterator;
#include<algorithm>
using std::transform;
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;

#include "point.h"
#include "polygon.h"

int main (){
    cout << setprecision(5);
    RegularPolygon pentagon(5, Point(0,0));
    cout << pentagon<<endl;

    pentagon.set_a(1);
    cout << pentagon << endl;
    pentagon.set_r(1);
    cout << pentagon << endl;
    pentagon.set_s(1);
    cout << pentagon << endl;

    cout << "Pentagon area with s=1: "<<pentagon.get_area() << endl;

    pentagon.add(1,'s');
    cout <<"Add one to s: "<< pentagon << endl;

    pentagon.mult(2,'s');
    cout <<"Mutiply s by two: "<< pentagon << endl;

    pentagon.set_r(4);
    vector<Point> vp = pentagon.generate_points();
    cout << "Pentagon vertices with r=4"<<endl;
    cout << vector_to_string(vp) << endl;


    RegularPolygon square(4, Point(0,0));
    square.set_s(4);
    cout << "Square vertices with s=4"<<endl;
    vp = square.generate_points();
    cout << vector_to_string(vp) << endl;

}
