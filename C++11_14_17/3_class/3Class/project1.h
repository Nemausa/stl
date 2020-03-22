#pragma once

#include <iostream>
using namespace std;
#include "time.h"

extern int g_abc;

namespace class_
{

    int main()
    {
        // 一：综述：类是我们自己定义的数据类型
        // 设计类要考虑的角度：
        // (1)站在设计和实现者的角度来考虑；
        // (2)站在使用者的角度来考虑；
        // (3)父类，子类

        // 二：类基础
        // (1)一个类是用户自己定义的数据类型，我们可以把类想象成一个命名空间
        // (2)一个类的构成：成员变量，成员函数（有许多特此的成员函数）
        // (3)我们访问成员时，如果是类对象，就是用对象名.成员名访问对象
        // 如果是对象指针，就用指针名->成员名来访问成员
        // (4)public成员，暴露给外界，供外界调用。
        // private成员提供各种实现类的细节方法，但不暴露给使用者，外界无法使用这些private成员。
        // (5)struct 是默认为public的class； 
        // (6)class成员默认是private;

        // 三:成员函数

        // 四:对象的拷贝
        // 对象本身是可以拷贝的：
        // 默认情况先，这种对象的拷贝，是每个成员变量逐个拷贝
        // 如果在Time中我们重新定义“赋值运算符”,就能够控制对象的拷贝行为

        // 五：私有成员

        /*Time mytime;
        mytime.hour_ = 12;
        mytime.minute_ = 12;
        mytime.second_ = 12;

        Time mytime2 = mytime;
        Time mytime3(mytime);*/
        //Time mytime4{ mytime };
        //Time mytime5 = { mytime };
        //mytime.millisecond = 100;  // 私有成员外界不能访问
        
        return 0;
    }
}