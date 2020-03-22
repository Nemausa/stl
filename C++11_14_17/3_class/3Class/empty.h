// project100.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

class A
{
public:
    void func() {}; //成员函数
    void func1() {}; //成员函数
    void func2() {}; //成员函数

                     //char ab; //成员变量，char类型占一个字节内存
    int ab; //int类型占4个字节
};

//类对象所占用的空间
int main()
{
    //std::cout << "Hello World!\n"; 
    A obja, objb;
    int ilen = sizeof(obja); //sizeof(A)   = 1 ，为什么sizeof(空类) = 1 而不等于0？
    cout << ilen << endl;

    //类的成员函数 不占用 类对象的内存空间
    //我们已经知道两点：
    //(1)成员函数不占用类对象的内存空间
    //(2)一个类对象至少占用1个字节的内存空间
    //obja.ab = 'c';
    //(3)成员变量是占用对象的内存空间
    obja.ab = 12;
    objb.ab = 24;

    //结论：成员变量是包含在每个对象中的，是占用对象字节的。
    //而成员函数虽然也写在类的定义中，但成员函数不占对象字节数的（不占内存空间）；

    //成员函数 每个类只诞生 一个（跟着类走），而不管你用这个类产生了多少个该类的对象；




    return 1;
}

