#pragma once

#include <iostream>
using namespace std;
#include <vector>

template<typename C>
class A
{
public:
    template<typename T2>
    A(T2 v1, T2 v2);  // 构造函数也引入自己的模板，和整个类的模板C没有关系
 

    template<typename T>
    void myft(T t)  // 成员函数模板
    {
        cout << t << endl;
    }

    C m_ic;
};

template<typename C>  // 先跟类的模板参数列表
template<typename T2> // 在跟构造函数自己的模板参数列表
A<C>::A(T2 v1, T2 v2)
{
    cout << v1 << v2 << endl;
}

template<typename T>
void myfunc(T v1, T v2)
{
    cout << v1 + v2 << endl;
}
