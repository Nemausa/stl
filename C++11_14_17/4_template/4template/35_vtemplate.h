
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_set>
#include <functional>
#include <queue>

using namespace std;
//
namespace _nmsp1
{
    //可变参模板：（Variadic Templates)：允许模板中含有0个 到 任意个 模板参数，在语法上也和传统模板不太一样，多了一个...

    //一：可变参函数模板
    //（1.1）简单范例
    //值得注意的内容：
    //a)我们一般把这个args称为一包 或者一堆 参数，而且这些参数的类型可以各不相同；
    //我们理解T这种类型的时候，不能把他理解成一个类型，你要理解成0到多个不同的类型，那自然，对应的参数args也应该是多个不同类型的参数；
    //b)这 一包参数中可以容纳0到多个模板参数，而且这些模板参数可以为任意的类型；
    //c)大家注意把名字理顺一下：
    //T后边带了...,所以，我们称呼T：可变参类型； 这个东西看起来是一个类型名，实际上里边包含的是0到多个不同的类型（一包类型）；
    //args：可变形参，既然T代表的是一包类型，那显然args代表的就一包形参；
    //d)在具体函数形参中，&的位置，出现在了类型名的后边。

    //（1.2）参数包的展开:展开套路比较固定，一般都是用递归函数的方式来展开参数；
    //要求我们在代码编写中，有一个参数包展开函数，和一个同名的递归终止函数，我们就是通过这两个函数把参数包展开的；

    template <typename... T>
    void myfunct1(T... args) //T：一包类型   ，args：一包形参
    {
        cout << sizeof...(args) << endl;   //sizeof...可变参数量
        cout << sizeof...(T) << endl;
    }

    //----------------------------
    //递归终止 函数
    void myfunct2()
    {
        cout << "参数包展开时执行了递归终止函数myfunc2()..." << endl;
    }

    template <typename T, typename...U>
    void myfunct2(const T& firstarg, const U&... otherargs) //一个参数，一包参数，这种可变参函数模板写法最适合参数包的展开
    {
        //cout << sizeof...(otherargs) << endl;
        cout << "收到的参数值为:" << firstarg << endl;
        myfunct2(otherargs...); //递归调用，注意写法...
    }

    void func()
    {
        /*myfunct1();
        myfunct1(10,20);
        myfunct1(10,25.8,"abc", 68);*/

        //myfunct2(10); //0
        myfunct2(10, "abc", 12.7);


        //myfunct2(10, "abc", 12.7);
        //myfunct2("abc", 12.7);
        //myfunct2( 12.7);
        //myfunct2();


    }
}
namespace _nmsp2
{
    //二：可变参类模板：允许模板定义中含有0到任意个模板参数；
    //（2.1）通过递归继承方式展开参数包
    template<typename...Args> class myclasst {}; //主模板

    template<> class myclasst<>  //0个模板参数的特化版本
    {
    public:
        myclasst()
        {
            printf("myclasst<>::myclasst()执行了,this = %p\n", this);
        }
    };

    template <typename First, typename... Others>
    class myclasst<First, Others...> : private myclasst<Others...> //偏特化
    {
    public:
        myclasst() :m_i(0)
        {
            printf("myclasst::myclasst()执行了,this = %p\n", this);
        }
        myclasst(First parf, Others...paro) :m_i(parf), myclasst<Others...>(paro...)
        {
            cout << "-------------------begin----------------" << endl;
            printf("myclasst::myclasst(parf,paro)执行了,this = %p\n", this);
            cout << "m_i=" << m_i << endl;
            cout << "-------------------end------------------" << endl;
        }
        First m_i;
    };

    void func()
    {
        //myclasst<int, float, double> myc;
        myclasst<int, float, double> myc(12, 13.5f, 23);
        //范例取材：标准库中的tuple（元组）


    }
}