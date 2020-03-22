#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include "women.h"
#include "men.h"
#include "human.h"

class BB
{
public:
    BB() :m_bm(100)
    {
        cout << "类B的构造 函数执行了" << endl;
    }

    // 拷贝构造函数
    BB(const BB& tmp)
    {
        m_bm = tmp.m_bm;
        cout << "类B 的拷贝构造函数" << endl;
    }

    virtual ~BB()
    {
        cout << "类B的析构函数执行了" << endl;
    }
    int m_bm;

};

class AA
{
public:
    AA():m_pb(new BB())
    {
        cout << "类A的构造函数执行了" << endl;
    }

    AA(const AA&tmp):m_pb(new BB(*(tmp.m_pb)))
    {
        cout << "类A的拷贝构造函数执行了" << endl;
    }

    //noexcept: 通知标准库我们这个移动构造函数不抛出任何异常,提高编译器工作效率
    AA(AA&& tmp) noexcept:m_pb(tmp.m_pb)  
    {
        tmp.m_pb = nullptr;
        cout << "类A的移动构造函数执行了" << endl;
    }

    // 拷贝赋值运算符
    AA& operator=(const AA& src)
    {
        if (this == &src)
            return *this;

        delete m_pb;
        m_pb = new BB(*(src.m_pb));
    }

    // 移动赋值运算符
    AA &operator=(AA &&src) noexcept
    {
        if (this == &src)
            return *this;

        delete m_pb;  // 先把自己的内存干掉
        m_pb = src.m_pb;  // 把对方的内存直接拿过来
        src.m_pb = nullptr;
        std::cout << "类A的移动赋值运算符" << endl;

        return *this;
    }

    virtual ~AA()
    {
        delete m_pb;
        cout << "类A 的析构函数执行了" << endl;
    }
private:
    BB *m_pb;
};

static AA getA()
{
    AA a;
    return a;
}

namespace move2
{
    


    int main()
    {
        // 一：对象移动的概念

        // 二：移动构造函数和移动赋值预算符概念
        // C++11 std::move 效率问题
        // 移动构造函数：C++11进一步提高程序效率
        // 说明：
        // (1)A移动B，那么A对象我们就不能再使用了
        // (2)移动：并不是把内存中的数据从一个地址倒腾到另一个地址，所有者变更
        
        // 拷贝构造函数：Time::Time(const Time&)  const左值引用
        // 移动构造函数：Time::Time(const Time &&)  右值引用

        // 移动构造函数和移动赋值运算符应该完成的功能
        // (1)完成必要的内存移动，斩断原对象和内存的关系
        // (2)确保移动后源对象处于一种"即便被销毁也没有什么问题"的一种状态，确保不再使用原对象

        
        // 三：移动构造函数演示
        //BB *p = new BB();
        //p->m_bm = 19;

        //BB *p2 = new BB(*p);  // 这种参数的new 方法会调用B的拷贝构造函数

        //delete p;
        //delete p2;

        //AA a = getA();
        // AA a2(std::move(a))  // std::move， 建立新对象，调用新对象a2移动构造函数
        //AA &&a3(std::move(a)); // 这里没有建立新对象，根本不会调用什么移动构造函数

        // 四：移动赋值运算符
        //AA a = getA();
        //AA a2;
        //a2 = std::move(a);

        // 五：合成的移动操作
        // 某些条件下，编译器能够合成移动构造函数，移动赋值运算符
        // (a)有自己的拷贝构造函数，拷贝赋值运算符或者自己的析构，那么编译器就不会为它合成移动构造函数和移动赋值运算符
        // 所以有些累是么有移动构造函数和移动赋值运算符
        // (b)如果么有自己的移动构造函数和移动赋值运算符，那么系统会调用我们自己写的拷贝构造函数和拷贝赋值运算符来代替。
        // (c)只有一个类没有定义自己版本的拷贝构造函数，且类的每个静态成员都可以移动时，编译器才会为该类合成移动构造函数或者移动赋值运算符
        // 什么叫成员可以移动
        // (1)内置类型是可以移动的
        // (2)类类型的成员，这个类要有对应的移动操作相关的函数，就可以移动。


        // 六：总结
        // (1)尽量给类增加移动构造函数和移动赋值运算符
        // (2)noexcept
        // (3)原对象要置空，让被移动对象那个随时处于一种能够被析构的状态
        // (4) 没有移动，会调用拷贝

        return 0;
    }

}
