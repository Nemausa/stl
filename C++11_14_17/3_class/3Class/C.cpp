#include <iostream>
#include "c.h"
#include "A.h"
using namespace std;

void C::callCAF(int x, A &a)
{
    a.data_ = x;
    cout << a.data_ << endl;
}

