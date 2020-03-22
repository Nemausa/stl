#pragma once
#include<iostream>
using namespace std;

#include "c.h"

class A
{
public:
    friend void C::callCAF(int x, A &a);  // 该函数是友元成员函数声明
    A(int i) :value_(i) {};
private:
    int data_;
    int value_;
    
};

class B: public A
{
public:
    B(int i, int j, int k):A(i),valueb_(k) {};

public:
    int valueb_;

};