#include<string>
using std::string;
#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include "proj11.h"

int main (){
    cout << boolalpha;

    Dict<string,bool> testing ("fart", true);

    testing.append("shart", false);
    testing.append("gopher", false);
    testing.append("torped", false);
    testing.append("rand", false);
    testing.append("fuck", false);
    testing.append("shit", false);

    cout << "test: " << testing << endl;
    cout << testing.size() << endl;

    testing.erase("shart");

    cout << "test: " << testing << endl;
    cout << testing.size() << endl;

    testing.erase("fart");

    cout << "test: " << testing << endl;
    cout << testing.size() << endl;

    // constructor
    Dict<string,long> d;
    // add
    d.append("bill", 10);
    d.append("rich", 20);
    // output
    cout << d << endl << endl;

    //copy
    Dict<string,long> d2(d);
    cout << d2 << endl;
    cout << "D2 SIZE: " << d2.size() << endl << endl;

    // add to existing key
    d2.append("bill", 100);
    // copy working?
    cout << d << endl << endl;
    cout << d2 << endl << endl;

    // exists
    cout << "Exists bill:"<<d.exists("bill")<<endl;
    cout << "Exists john:"<<d.exists("john")<<endl;
    // get_value
    cout << "Value of rich:"<<d.get_value("rich")<<endl;
    // order should be different now
    cout << d << endl;
    // get_value throws on bad key
    try{
	d.get_value("john");
    }
    catch (range_error &e){
	cout << "bad get_value "<<e.what()<<endl;
    }

    // make the array grow
    d.append("fred", 30);
    d.append("bob", 40);
    d.append("irving", 50);
    d.append("john",60);
    cout << endl;
    cout <<"Size 6:"<< d << endl<<endl;

    // assignment
    Dict<string,long> d3;
    d3 = d;

    // erase
    d.erase("fred");
    // assignment working?
    cout << "Value of irving:"<<d.get_value("irving")<<endl;
    cout << d << endl;
    cout << d.size() << endl<<endl;
    cout << "Value of rich:"<<d3.get_value("rich")<<endl;    
    cout << d3 << endl;
    cout << d3.size() << endl;

}
