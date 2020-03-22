//////////////////////////////////////////////////////////////////////////
//  @file     add.h
//  @author   Morris
//  @date     2019-02-17
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-02-17
//  -added 
//  @remark   类型转换
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef CAST_H
#define CAST_H
#include <iostream>
using namespace std;
namespace cast_
{
    int main()
    {
        // 一：隐式类型转换：系统自动自行，不需要程序开发人员介入
        int m = 3 + 45.6;  // 48 把小数部分截掉，也属于隐式转换的一种行为

        // 二：显示类型转换（强制类型转换）
        // int k = 5 % 3.2;  // 语法错
        // int k = 5 % (int)3.2;  // OK, C语言风格的强制类型转换
        // int k = 5 % int(3.2);  // 函数风格的强制类型转换（C语言风格的强制类型转换）

        // C++强制类型转换分4种：我们现在写程序应该使用C++风格的强制类型转换。
        // 这4中强制类型转换，分别用于不同的目的，每一个都又不同的名字。
        // 提供4种类的目的：提供更丰富的含义和功能，更好的类型检查。
        // a)static_cast
        // b)dynamic_cast
        // c)const_cast
        // d)reinterpret_cast
        // 这4个强制类型转换被称呼为“命名的强制类型转换（因为他们每一个都有一个名字且名字各不相同)）;
        // 通用形式
        // 强制类型转换名<type>(express)
        // 强制类型转换名 是上面a,b,c,d之一
        // type:转换的目标类型
        // express：你要转换的值

        // (2.1) static_case:静态转换，大家就可以理解成"正常转换"，编译时就会进行类型检查。
        // 代码中要保证转换的安全性和正确性，static_cast含义跟C语言的强制类型转换差不多
        // C风格的强制类型转换，一个编译器能够进行的隐式类型转换，都能用static_cast
        // 可用于：
        // a)相关类型转换，比如整型和实型之间的转换
        // b)子类转换成父类
        // c)void *与其他类型指针之间的转换， void*：无类型指针：可以指向任何类型（万能指针）
        //int i = 10;
        //int *p = &i;
        //void *q = static_cast<void *>(p); // int *转换成void*
        //int *m = static_cast<int *>(q);

        // 不能用于：
        // a）一般不能用于指针类型之间的转换 比如int* 转换double*, float*转double *


        // (2.2)dynamic_cast:重要用于运行时类型识别和检查。主要用于父类型和子类型之间的
        // 转换用的（父类型指针指向子类型对象，然后用dynami_cast把父类型指针往子类型指针转）
        // 第三种 第10节

        // (2.3)const_cast: 取出指针或引用的const属性。能够将const性质转换调
        // 编译时就会进行类型转换
        const int ai = 90;
        const int *pai = &ai;
        int *pai2 = const_cast<int *>(pai);
        *pai2 = 120;  // 这种写值得行为属于未定的行为

        cout << ai << endl;
        cout << *pai << endl;

        // (2.4)reinterpret_cast:编译时会进行类型转换的检查
        // reinterpret:重新解释(将操作内容解释为另一种不同的类型，能把操作数的类型都转换了)
        // 处理无关类型的转换，也就是两个转换类型之间没有关系，就等于乱转，很随意
        // a)将一个整型（地址）转换成指针，一种类型指针转换成另一种类型指针，按照转换后的内容重新解释内存中的内容
        // b)可以从一个指针类型转换成整型
        // 被认为是危险的转换：随便转都可以，编译器不报错
        int i = 10;
        int *pi = &i;
        int *p2 = reinterpret_cast<int *>(&i);
        char *pc = reinterpret_cast<char *>(pi);
        void *pvoid = reinterpret_cast<void *>(pi);

        // 总结：
        // 强制类型转换，不建议使用，强制类型转换能够抑制编译器报错
        // 学习的目的： 认识这些类型转换符，方便阅读代码
        // reinterpret_cast危险,const_cast意味着设计缺陷
        // 不要再使用C语言的类型转换，实在要用就用C++的
        // 一般static_cast 和reinterpret_cast就能够取代c语言风格类型的转换

        return 0;
    }

}
#endif
