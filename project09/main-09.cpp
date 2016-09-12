#include<iostream>
using std::cout; using std::endl;
#include <initializer_list>
using std::initializer_list;
#include <stdexcept>
using std::range_error;
#include "class-09.h"

int main (){

  SparseVector vec(1000,1337,{
    {873,3}, {999,-44385039845}, {2,9}, {333,50},
    });

  SparseVector temp(1);

  temp = vec * 2;

  SparseVector vec2(0,3);



  //for (int i = 0; i < temp.size(); i++)
    //cout << temp[i] << endl;
}
