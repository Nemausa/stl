#pragma once
#include <iostream>
using namespace std;
#include "men.h"
#include "func.h"
#include "A.h"
#include "C.h"


//class A
//{
//private:
//    int data_;
//    friend class C; // 这就是友元类的声明，虽然此时类C没有定义，但是系统没有报错。
//};
//
//class C
//{
//
//public:
//    void callCAF(int x, A &a)
//    {
//        a.data_ = x;  // 正常情况下就不可以
//        cout << a.data_ << endl;
//    }
//};

namespace friend_
{

    void main()
    {
        // 友元函数：这是个函数
        // 只要让函数func成为类men的有友元函数，哪个func这个函数就能访问类的所有成员（变量和函数）,private,public,protected
        //men men;
        //func(men);

        // 总结：友元函数func：是个函数，通过声明为某个类的友元函数，它就能访问类的所有成员

        // 二：友元类 ：类可以把其他的类定义成友元类，如果你是我的友元类，那么你就能在你的成员函数中访问我的所有成员
        // 我们修改类a，让类c成为类a的朋友，也就是让类c成为类a的友元类。
        //a a;
        //c c;
        //c.callcaf(3, a);

        // 注意：每个类都负责控制自己的友元类和友元函数，所以：
        // (a)友元关系不能被继承
        // (b)友元关系是单向的，比如上面类c是a的友元类，但并不表示类a是类c的友元类；
        // (c)友元关系没有传递性的，比如类b是类a的友元类，类c是类b的友元类，这并不表示类c是类a的友元类。

        // 三：友元成员函数
        // 写这种友元成员函数，必须要注意代码组织结构，因为里面有声明和定义的这总依赖关系。

        //A a;
       // C c;
        //c.callCAF(3, a);

        // 总结：friend
        // 优点：运行在特定的情绪某些成员函数访问protected，private成员，
        // 缺点：这也破坏了类的封装性，降低了类的可靠性和访问性。


    }

}