#include<string>
using std::string;
#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include "proj10.h"

int main (){
    cout << boolalpha;

    // constructor
    Dict<string,long> d;
    // add
    d.add("bill", 10);
    d.add("rich", 20);
    // output
    cout << d << endl << endl;
    /*
    //copy
    Dict<string,long> d2(d);
    cout << d2 << endl << endl;


    // add to existing key
    d2.add("bill", 100);
    // copy working?
    cout << d << endl << endl;
    cout << d2 << endl << endl;


    // exists
    cout << "Exists bill:"<<d.exists("bill")<<endl;
    cout << "Exists john:"<<d.exists("john")<<endl;
    // get_value
    cout << "Value of bill:"<<d.get_value("bill")<<endl;

    // get_value throws on bad key
    try{
	d.get_value("john");
    }
    catch (range_error &e){
	cout << "bad get_value "<<e.what()<<endl;
    }


    // make the array grow
    d.add("fred", 30);
    d.add("bob", 40);
    d.add("irving", 50);
    d.add("john",60);
    cout << endl;
    cout << d << endl<<endl;


    // assignment
    Dict<string,long> d3;
    d3 = d;

    // erase
    d.erase("bob");
    // assignment working?
    cout << d << endl<<endl;
    cout << d3 << endl<<endl;
    */
}
