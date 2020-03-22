#pragma once
#include<iostream>
using namespace std;
#include "human.h"


class Men:public Human
{
public:
    Men();
    ~Men();
    using Human::public_fun;

    void eat() override;
    void eat2();
    void testfunc()
    {
        cout << "testfunc" << endl;
    }
private:
    void funcmen() const
    {
        std::cout << "funcmen()" << endl;
    }

    // 因为友元函数不属于类成员，所以友元函数不收public，protected，private；
    friend void func(const Men &men);  // 该函数是友元函数
};