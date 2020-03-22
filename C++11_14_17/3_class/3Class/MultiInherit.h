#pragma once

#include "men.h"
#include "women.h"
#include "human.h"
#include <iostream>
using namespace std;

//class MA
//{
//public:
//    MA(int i, int j, int k=5)
//    {
//
//    }
//
//};
//
//class MB : public MA
//{
//
//public:
//    //MB(int i, int j, int k):MA(i,j,k){}
//    using MA::MA;  // 继承MA的构造函数，using::让某个名字在当前的作用域可见
//                  // 遇到这条代码，基类的每个构造函数，都生成一个与之对应的派生类构造函数。
//
//    // 如果基类MA的构造函数有默认参数的话，那么编译器遇到这种using MA::MA的时候，就会帮我们在派生类MB中构造出多个构造函数。
//    // (a)第一个构造函数是带有所有参数的构造函数
//    // (b)其余的构造函数，每个分别忽略掉一个默认参数
//    // MB(int i, int j, int k):MA(i,j,k){}
//    // MB(int i, int j):MA(i,j){}
//    // 如果类MB，只含有using MA::MA 从MA继承来的构造函数的话，那么编译器是会给它合成默认的构造函数的。
//};


class Grand
{
public:
    Grand(int i) :m_val(i) { cout << "Grand构造函数" << endl; }
    virtual ~Grand() { cout << "Grand析构函数" << endl; }

    void myinfo()
    {
        cout << m_val << endl;
    }
public:
    int m_val;
    static int m_static;

};
// 为了能够使用，我么定义这个静态成员变量(分配内存)
int Grand::m_static = 5;  // 如果代码中不用m_static，那么可以不定义。

class MA : virtual public Grand
//class MA : public virtual Grand
{
public:
    MA(int i) :Grand(i), m_vala(i) { cout << "MA构造函数" << endl; } // 每个子类的构造函数，负责解决自己父类的初始化问题。
    virtual ~MA() { cout << "MA析构函数" << endl; }

    void myinfo()
    {
        cout << m_vala << endl;
      
    }

public: 
    int m_vala;
    //int m_static;
};

class MA2 : public virtual Grand
{
public:
    MA2(int i) :Grand(i), m_vala(i) { cout << "MA2构造函数" << endl; } // 每个子类的构造函数，负责解决自己父类的初始化问题。
    virtual ~MA2() { cout << "MA2析构函数" << endl; }

    void myinfo()
    {
        cout << m_vala << endl;

    }

public:
    int m_vala;
    //int m_static;
};

class MB
{
public:
    MB(int i) :m_valb(i) { cout << "MB构造函数" << endl; }
    MB() { cout << "MB默认构造函数" << endl; }

    virtual ~MB() { cout << "MB析构函数" << endl; }
    void myinfo()
    {
        cout << m_valb << endl;
    }

public:
    int m_valb;
};

class MC : public MA,public MA2, public MB
{
public:
    //MC(int i, int j, int k) :MA(i), MB(j), m_valc(k) { cout << "MC构造函数" << endl; }
    //MC(int i, int j, int k) :MA(i), MA2(i), m_valc(k) { cout << "MC构造函数" << endl; };
    MC(int i, int j, int k) :MA(i), MA2(i),Grand(i), m_valc(k) { cout << "MC构造函数" << endl; };

    virtual ~ MC()
    {
        cout << "MC析构函数" << endl;
    }

    void myinfoC()
    {
        cout << m_valc << endl;
        MA::myinfo();
        MB::myinfo();

    }
public:
    int m_valc;
};


//class MA
//{
//public:
//    MA(int v) {}
//};
//
//class MB
//{
//public:
//    MB(int v) {}
//};
//
//class MC:public MA, public MB
//{
//public:
//    using MA::MA; // C(int v):A(v) {}
//    using MB::MB; // C(int v):B(v) {}
//    // 如果一个类从他的基类中继承了先沟通呢的构造函数，这个类必须为该构造函数定义自己的版本。
//    MC(int v) :MA(v), MB(v) {};
//
//};
namespace multi
{
    int main()
    {
        // 一：继承的构造函数
        // 一个类值继承其直接基类的构造函数，默认，拷贝，移动构造函数是不能被继承的。
        // 如果基类含有多个构造函数，则多数情况下，派生类会继承所有这些构造函数，但如下情况例外：
        // (1)如果你在派生类中定义的构造函数与基类构造函数有相同的参数列表，那么从基类中继承来的构造函数会被你派生类中的定义覆盖掉。
        // (2)默认，拷贝，移动构造函数不会被继承

        // 二：多重继承  从多个父类来产生出子类
        //MC cteste(10, 20, 50);

        // 派生类会包含每个基类的子对象

        // (2.2)静态成员变量，不属于对象
        //Grand::m_static = 1;
        //MA::m_static = 2;

        // (2.3)派生类构造函数与析构函数
        // (a)构造一个派生类对象将同时构造并初始化所有的基类子对象。
        // (b)派生类的构造函数初始化列表值初始化它的直接基类，每个类的构造函数都负责初始化它的直接基类，就会让所有类都得到初始化。
        // (c)派生类构造函数初始化列表将实参分别传递给每个直接基类，基类的构造顺序跟"派生列表"中基类的出现顺序保持一致。
        // 概念：显示的初始化基类和隐式的初始化基类问题


        // （2.4）从多个父类继承构造函数
        // 子类要定义同参数的构造函数 自己的版本

        // 三：类型转换
        // 基类指针可以指向一个派生类对象：编译器帮助我们隐式指向这种派生类到基类的转换，转换成功的原因是每个派生类对象都包含一个基类对象部分。
        // 所以基类的引用或者指针可以板顶到基类对象的这部分上来
        // Grand *pg = new MC(1,2,3)
        // MA *pa = new C(1,2,3);
        // MB *pb = new C(1,2,3);
        // C myc(1,2,3);
        // Grand mygrand(myc)

        // 四：虚基类(virtual base class)，虚继承
        // 派生列表中，同一个基类只能出现一次，但是如下情况例外：
        // (a)派生类可以通过它的两个直接基类分别继承同一个间接基类；
        // (b)直接继承某个基类，然后通过另一个基类间接继承该类。
        // 这样导致Grand构造了两次
        // 虚基类：无论这个类在继承中出现多少次，派生类中，都只会包含唯一一个共享的虚基类子内容。
        // 大家观察到一个现象，这种继承只对MC有意义，其实对于MC的父类MA， MB没有意义；
        // 换句话说，MA, MA2从Grand类虚继承，只影响从MA,MA2这些类中进一步派生出的类MC，而对MA,MA2本身没有什么影响。
        // 每个Grand的子类都要虚继承Grand类，那么才能保证Grand的孙类虚继承Grand类。
        // 只要子类中都加virtual继承，那么Grand类自然成为了"虚基类"，virtual::表达一种意愿：表示后续从我派生的类共享一份数据。

        // 特别说明：
        // (1)现在是C类初始化Grand类，如果C类以后有了孩子，则有C类的子类初始化Grand类，换句话说：虚基类由最底层的类来初始化
        // (2)初始化顺序问题：先初始化虚基类部分，然后在按派生列表中出现的顺序来初始化其他类
        // (3)多个虚基类，哪个虚基类先初始化呢  按照派生列表中的直接基类往回溯，看是否这些基类含所有虚基类，先追溯到哪个先初始化哪个。


        // 总结
        // 小心虚继承，不太提倡使用
        // 简单，不容易出现二义性，实在必要才使用多继承，能用单一继承劲量用单继承
        MC ctest(1, 2, 3);
        //ctest.m_val=10;


        return 0;
    }

}
