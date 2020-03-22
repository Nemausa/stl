#include "men.h"
#include <iostream>


Men::Men()
{
    cout << "执行了Man::Man()" << endl;
}

void Men::eat()
{
    cout << "男人喜欢吃米饭" << endl;
}


void Men::eat2()
{
    cout << "Men::eat2()" << endl;
}

Men::~Men()
{
    cout << "Men::~Men()" << endl;
}