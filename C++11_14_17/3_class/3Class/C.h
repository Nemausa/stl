#pragma once
#include<iostream>
using namespace std;

class A;

class C
{

public:
    void callCAF(int x, A& a);  // 只有public才能成为其他类的友元成员函数。

};