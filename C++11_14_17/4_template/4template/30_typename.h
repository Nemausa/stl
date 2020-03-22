//////////////////////////////////////////////////////////////////////////
//  @file     typename.h
//  @author   Morris
//  @date     2019-03-19
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-03-19
//  -added 
//  @remark   
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef TYPENAME_H
#define TYPENAME_H
#include <iostream>
using namespace std;
#include <string>


namespace typename_
{
    template<typename T>
    typename T::size_type getlength(const T &c)
    {
        if (c.empty())
            return 0;
        return c.size();
    }

    // 我们要把函数指针作为某个函数的参数进行传递
    // 函数指针要想做函数参数就需要
    typedef int(*FunType)(int, int);  // 定义一个函数指针类型
    int mf(int a, int b)
    {
        return 1;
    }

    void testfunc(int a, int b, FunType funcpoint)
    {
        int result = funcpoint(a, b);
        cout << result << endl;
    }



    // 可调用对象所代表的类，不懂先去学习"未归类知识点"第一节
    class tc
    {
    public:
        tc() { cout << "构造函数" << endl; }
        tc(const tc&t) { cout << "拷贝构造" << endl; }

        // 重载圆括号
        int operator()(int a, int b) const
        {
            return a + b;
        }
    
    };

    template<typename T, typename F=tc>
    //void tfunc(const T &a, const T &b, F funcpoint)
    void tfunc(const T &a, const T &b, F funcpoint = F())
    {
        cout << funcpoint(a, b) << endl;
    }

    int main()
    {
    
        // 一：typename的使用场合
        // (1)在类模板定义中，表明其后的模板参数是类型参数
        // (2)使用类的类型成员，用typename来标识一个类型
        //string mystring = "I love China";
        //string::size_type size = getlength(mystring);

        // 二：函数指针做其他函数的参数

        // testfunc(1, 2, mf);

        // 三：函数模板趣味用法范例
        // tfunc(1, 2, mf);

        //tc obj;
        //tfunc(3, 4, obj);
        // tfunc(3, 4, tc());  // 奇特
        cout << tc()(1, 2) << endl;

        // 四：默认模板参数
        // (a)类模板，类模板后面必须用<>来提供额外的信息，<>表示这是一个模板
        // (b)函数模板：老标准只能为类模板提供默认的模板参数，新标准可以为函数模板提供默认参数



        return 0;
    }


}



#endif