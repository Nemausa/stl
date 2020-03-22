#pragma once
#include <iostream>
using namespace std;
#include <map>
#include <functional>


//class TestInt
//{
//public:
//    // 定义一个函数指针类型，代表的函数带一个int形参，没有返回类型
//    typedef void(*tfpoint)(int);
//    using tf = void(*)(int);
//public:
//    // explicit:禁止隐式类型转换
//    TestInt(int x = 0) :m_i(x)  // 类型转换构造函数，本构造函数就可以将一个int数字转换成TestInt
//    {
//        if (x < 0) m_i = 0;
//        if (x > 100) m_i = 100;
//    }  
//
//    // 类型转换运算符，可以把本类类型对象转换成其他类型
//    //operator int() const
//    explicit operator int() const
//    {
//        return m_i;
//    }
//
//    
//public:
//    static void mysfunc(int v)  // 静态成员函数
//    {
//        int test = 1;
//    }
//
//    // 新的类型转换运算符，能把本类类型对象转换成一个函数指针类型
//    operator tfpoint()  // const不是必须加的，所以这里不加
//    {
//        // 必须返回一个函数指针
//        return mysfunc;
//    }
//public:
//    int m_i;
//};
//
//class CT1
//{
//public:
//    CT1(int ct) {}
//};
//
//class CT2
//{
//public:
//    CT2(int ct) {}
//};
//
//void testfunc(const CT1 &C) {}
//void testfunc(const CT2 &C) {}

class CT
{
public:
    void ptfunc(int temp)
    {
        cout << "ptfunc普通成员函数 vallue = " << temp << endl;
    }

    virtual void virtualfunc(int temp)
    {
        cout << "virtual函数被调用 value= " << temp << endl;
    }

    static void staticfunc(int temp)
    {
        cout << "static函数被调用 value = " << temp << endl;
    }

    int m_a;
    static int m_static;
};

int CT::m_static = 0;

namespace convert
{

    int main()
    {
        // 我们需要通过转换构造函数，和类型转换运算符来做到类型转换
        // 一：类型转换构造函数，比如，他们能够把一个数字转换成一个类对象
        // 构造函数种类：特点回顾
        // a)以类名作为函数名
        // b)没有返回值
        // 有一种构造函数 叫类型转换构造函数，主要能力是：它可以将某个其他的数据类型转换成该类类型的对象
        // 类型转换构造函数的特点
        // a)只有一个参数，该参数有不是本类的const引用。该参数其实就是带转换的数据类型，所以显然待转换的数据类型都不应该是本类类型
        // b)在类型转换构造含漱液中，我们应该指定转换的方法
        //TestInt ti = 12;  // 隐式类型转换  将数字12转换成TestInt对象
        // 编译器用12这个数字通过调用TestInt类的类型构造函数来创建一个临时的TestInt对象，并把这个对象构造到了ti的预留空间里面去了。
        //TestInt t2(22);  // 调用了类型转换构造函数，但这里没有进行隐式类型转换

        // 二：类型转换运算符(类型转换函数)：能力和类型转换构造函数能力相反。
        // 是特殊的成员函数，它能够将一个类类型对象转换成某个其他数据类型
        // 格式：
        // operator type() const
        // a)const是可选项，const表示一般不应该改变待转换对象的内容，但不是必须有const
        // b)type:表示转换成的某种类型。只要是能够作为函数返回的类型，都可以。数组指针，函数指针，引用等类型都可以
        // c)类中转换运算符，没有形参(形参列表为空),因为类型转换运算符都是隐式的，所以根本也没有办法给它传递参数。
        // 同时也不能指定返回类型，但是它却能返回一个type指定的类型的值的。
        // d)必须定义为类的成员函数。

        //TestInt ti = 12;
        //TestInt t2;
        //t2 = 6;

        // int k = static_cast<int>(t2);  // 调用operator int() const
        //int k = t2 + 5; // 调用operator int() const将t2转换成int
        //int k2 = t2.operator int() + 5; // 显示调用，没有形参，所以()内为空

        // (2.1)显示类型转换运算符
        // (2.2)有趣范例：类对象转换成函数指针
        //TestInt myi(12);
        //myi(123); // 看起来是个可调用对象的感觉，相当于调用了两个函数：1）类型转换运算符[转换成函数指针类型],2)通过函数指针调用具体的函数
        //(myi.operator TestInt::tfpoint())(123);


        // 三：类型转换二义性问题
        // 二义性：这么干也行，那么干也行，导致编译器不知道该怎么干，所以编译器只能报错
        // 建议：在一个类中，尽量只出现一个类型转换运算符
        // testfunc(100);  // 二义性，因为100是个int类型，可以转成成CT1对象，也可以转换成CT2类型对象
        // testfunc(CT1(100)); // 明确调用，这种手段表明代码设计的不好


        // 四：类成员函数指针  是个指针，指向类成员函数
        // (4.1)对于普通成员函数
        // 格式：  类名::*函数指针变量名   来声明普通成员函数指针
        // &类名::成员函数名              来获取类成员函数地址   这个是真正的内存地址
        // 定义一个普通的类成员函数指针
        //void (CT::*mypointpt)(int);  // 一个类成员函数指针变量的定义，变量名为mypointpt
        //mypointpt = &CT::ptfunc;   // 类成员函数指针变量被赋值

        // 大家注意：成员函数是属于类的，不属于类对象，只要有类在就有成员函数地址在。
        // 但是你若要使用这个成员函数指针，就必须把它绑定到一个类对象才能调用
        // 使用函数指针格式：类对象名.*函数指针变量名
        CT ct, *pct;
        //pct = &ct;
        //(ct.*mypointpt)(100);  // 对象ct，调用指针变量mypointpt所指向的成员函数:ptfunc
        //(pct->*mypointpt)(100); 

        // (4.2)对于虚函数
        void(CT::*mypointvirtual)(int) = &CT::virtualfunc; // 这是个真正的内存地址
        // 也必须要绑定到一个类对象才能调用
        (ct.*mypointvirtual)(100);
        (pct->*mypointvirtual)(100);

        // （4.3）对于静态成员函数
        // 使用"*函数指针变量名"来声明静态成员函数指针，使用"&类名::成员函数名"来获取类成员地址，这个也是真正的地址
        // 定义一个静态的类成员函数指针并赋值
        void(*mypointstatic)(int) = &CT::staticfunc;
        mypointstatic(100);  // 直接使用静态成员函数指针名即可调用


        // 五：类成员变量指针
        // (5.1)对于普通成员变量
        int CT::*mp = &CT::m_a;  // 定义一个类成员变量指针，大家注意这里的写法  并不是真正意义上的指针
        // 它不是指向某个内存中的某个地址，而是该成员变量，与该类对象指针之间的偏移量
        ct.*mp = 189;  // 通过类成员变量指针来修改成员变量值，等价于ct.ma = 189;

        // (5.2)对于静态成员变量
        // 这种指向静态成员变量的指针，是有真正的内存地址。
        int *stcp = &CT::m_static;  // 定义静态成员变量指针
        *stcp = 796;  // 等价于CT::m_static = 796

        // 六：总结
        // C++对象模型

        return 0;
    }
}
