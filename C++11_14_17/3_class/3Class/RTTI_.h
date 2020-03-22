#pragma once

#include <iostream>
using namespace std;
#include "human.h"
#include "men.h"
#include "women.h"


namespace RTTI_
{
    void main()
    {
        // 一：RTTI是什么（RUN TIME TYPE Identification):运行时类型识别
        // 通过运行时类型识别，程序能够使用基类指针后者引用来检查这些指针或者引用所指的对象的实际派生类型。
        Human *phuman = new Men;
        Human &q = *phuman;
        // RTTI我们可以把这个称号看成是一种系统提供给我们的一种，或者一种功能，这种功能或者能力通过两个运算符来体现。
        // (1)dynamic_cast运算符：能够将基类的指针或者引用安全的转换为派生类的指针或者引用。
        // (2)typeid运算符：返回指针或者引用所指对象的实际类型。
        // 老师补充：要想让RTTI的这两个运算符能够正常工作，那么基类中必须至少有一个虚函数，
        // 不然这两个运算符工作的结果可能跟我们预期的结果不一致。
        // 因为只有虚函数的存在，这两个运算符就会使用指针或者引用所绑定的对象的动态类型。
        phuman->eat();

        // 二：dynamic_cast运算符：如果该运算符能够转换成功，说明这个指针实际上是要转换
        // 到的那个类型，这个运算符能够帮我们做安全检查。
        //Men *p = (Men *)(phuman);  // 通过C语言风格的强制类型转换，硬把指针转换成Men *
        //p->testfunc();   // 能够正常的调用Men类的成员函数

        //Men *pmen = dynamic_cast<Men*>(phuman);
        //if(pmen != nullptr)
        //{
        //    cout << "phuman 实际是个Men类型" << endl;
        //    // 在这里操作Men类里面的成员函数，成员变量能够操作并且安全的操作。
        //}
        //else
        //{
        //    cout << "fail" << endl;
        //}

        // 对于引用，如果用dynamic_cast转换失败，则系统会抛出一个std::bad_cast异常。 try{} ...catch(){};
        //try
        //{
        //    Men &men = dynamic_cast<Men &>(q);  // 转换不成功，则流程直接进入到catch中，如果转换不成功，流程继续走下去。
        //    // 走到这里表示转换成功
        //    cout << "phuman实际是一个Men类型" << endl;
        //    // 在这里调用类的Men成员函数是安全的。
        //    men.testfunc();
        //}
        //catch(std::bad_cast)
        //{
        //    cout << "phuman实际不是一个Men类型" << endl;
        //}

        // typeid(类型/指针/引用),也可能typeid(表达式)
        // 拿到对象类型信息，typeid就会返回一个常量对象引用，这个常量对象是一个标准库类型type_info（类/类类型)
        // typeid主要是为了比较两个指针是否指向同一种类型的对象。
        // 比较对象时，看的是new出来的对象或者指针指向的哪个对象，和定义该指针时定义的类型没关系
        // 基类必须有虚函数，否则这些比较都会不成立
        // 只有基类有虚函数时，编译器才会对typeid()中的表达式求值，否则如果某个类型不含有虚函数
        // 则typeid()返回的是表达式的静态类型(定义时的类型)，既然定义了类型，编译器就不需要对表达式求值也知道表达式的静态类型。

        // 四：typeinfo类
        // typeid就会返回一个常量对象的引用，这个常量对象时一个标准库类型typeinfo(类/类类型)
        // (a)name:获取名字,返回一个C风格的字符串
        // (b)== !=

        // 五：RTTI与函数表
        // 在C++中，如果类含有虚函数，编译器就会对该类产生一个虚函数表。
        // 虚函数表里面有很多项，每个项都是一个指针，每个指针指向的都是这个类里的各个虚函数的入口地址。
        // 虚函数表项里，第一个项很特殊，它指向的不是虚函数的入口地址，它指向的实际上是咱们这个类所关联的type_info对象。
        // phuman对象里有个我们看不见的指针，这个指针指向谁，指向的是这个对象所在类Men里的虚函数表。


        const type_info &tp = typeid(*phuman);
        cout << tp.name() << endl;  // Class Men 
       /* cout << typeid(*phuman).name() << endl;
        cout << typeid(q).name() << endl;*/

        Human *phuman1 = new Men;
        Men *pmen = new Men;
        if(typeid(*phuman1) == typeid(*pmen))
        {
            cout << "phuman1和pmen指向的类型相同" << endl;
        }

        if(typeid(*phuman1) == typeid(Men))
        {
            cout << "phuman1指向Men" << endl;
        }


    }

}