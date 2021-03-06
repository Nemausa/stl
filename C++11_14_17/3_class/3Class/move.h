﻿#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include "women.h"
#include "men.h"

namespace move_
{

    int main()
    {
        // 一：左值和右值
        // 左值：能用在赋值语句等号左侧的东西，它能够代表一个地址
        // 右值：不能作为左值的就是右值，右值不能出现在赋值语句中等号的左侧
        // 结论：C++一条表达式，要么是右值，要么是左值，但是左值有时候能被当做右值使用
        // int i = i + 1; // i是个左值，不是个右值，虽然它出现了在等号的右边。
                       // i用在等号右边的时候，我们说i有一种右值属性（不是右值）
                       // i出现在等号左边，用的是i代表的内存中的地址，我们说i有一种左值属性
        // 一个左值，它可能同时具有左值和右值属性
        // 用到左值得运算符有哪些：
        // 整个赋值语句的结果仍然是左值
        // a)赋值运算符
        //int a;
        //(a = 4) = 8;

        // b) 取地址 &
        // c) string， vector下标[]都需要左值,迭代器
        //string abc = "I Love China";
        //abc[0];
        //vector<int>::iterator iter;
        //iter++; iter--;

        // 通过一个运算符在一个字面值上能不能操作，我们就可以判断运算符是否用到的是左值

        // 左值表达式就是左值，右值表达式就是右值
        // 左值：代表一个地址，所以左值表达式的求值结果，就是一个对象，就得有地址。
        // 求值结果为对象的表达式，不代表一定是左值，具体在分析。


        // 二：引用分类
        // 三种形式的引用
        // (1)左值引用(绑定到左值)
        // (2)const引用(常量引用),也是左值引用，我们不希望改变值得对象
        //int value = 3;
        //const int &ref = value;
        //ref = 4;
        // (3)右值引用(绑定到右值):它是个引用
        //int &&refrightvalue = 3;
        //refrightvalue = 4;

        // 三：左值引用
        // 引用左值，绑定到左值上，没有空引用的说法，所以左值引用初始化的时候就绑定左值
        //int a = 1;
        //int &b{ a };
        ////int &c;  // 错误引用必须初始化
        ////int &c = 1;  // 不可以，左值引用不能绑定到右值上，必须绑定左值。
        //const int &c = 1;  // const引用可以绑定到右值上，所以const特殊，相当于如下语句
        //                   // int temp = 1;
        //                   // const int &c = temp;


        // 四：右值引用：就是引用右值，也就是说绑定到右值
        // 必须是绑定到右值得引用
        // 希望用右值引用来绑定一些即将销毁的或者是一些临时的对象上。
        //int &&ret = 3;  // 右值引用大家可以理解成对象的名字

        //string strtest{ "I love China!" };
        //string &RL{ strtest };
        //// string &RR{ "I love China!" }; 临时变量被系统当做引用
        //const string &r3{ "I love China!" };  // 可以，创建个临时变量，绑定到左值r3上
        ////const 引用不但可以绑定右值，还可以执行到string的隐式类型转换，并将所得到的值放到string临时变量中

        ////string &&r4{ strtest };  // 不可以，右值引用不能绑定到左值
        //string &&r5{ "I love China" };  // 可以绑定到一个临时变量，临时变量的内容 I love China
        //int i;
        //int &&r3 = i * 100;  // 可以，右值引用绑定到右值
        //// int &r4 = i * 100;  // 不可以，左值引用不能绑定到右值

        //const int &r4 = i * 100;  // 绑定到右值

        // 总结：返回左值引用的函数连同赋值，下标，解引用和前置递增递减运算符，都是返回左值表达式的例子；我可以将一个左值引用绑定到这类表达式上
        // 返回非引用类型的函数，连同算术，关系，位以及后置递增递减运算符，都生成右值。不能讲一个左值引用绑定到这类表达式上，但是
        // 我们可以将一个const的左值引用或者一个右值引用绑定到这类表达式上。
        //int i = 100;
        //(++i) = 199; // i被赋值成199

        // i++;先用后加，为什么是右值表达式
        // i++先产生一个临时变量temp记录i的值用于使用目的，再给i+1，接着返回这个临时变量，临时变量这个东西右值
        //int r1 = i++;
        // 重点强调：
        // (1)r1虽然是右值引用，但是r1本身是左值（把r1看成一个变量），因为他在=左边待着
        // (2)所有的变量，看成左值，因为他们是有地址的
        // (3)任何函数里面的行参都是左值，void f(int i,int &&w)w是右值引用，但是w本身是左值
        // (4)临时对象时右值

        // 右值引用的目的
        // a)C++11引入，&&，代表一种新的数据类型
        // b)提高程序运行效率，把拷贝对象编程移动对象来提高程序运行效率
        // c)移动对象如何发生。&&（应付移动构造函数，移动赋值运算符)


        // 五：std::move函数
        // C++标准库里面的新函数
        // std::move的能力只有一个，就是把左值强制转换成右值
        //int i = 10;
        //int &&r20 = std::move(i);  // 把一个左值变成一个右值

        //string st = "I lvoe China!";
        //string def = std::move(st);  // 触发了string的移动构造函数

        // 六：左值右值引用总结说明

        return 0;
    }

}
