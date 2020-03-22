#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include "men.h"
#include "women.h"

class CTempValue
{
public:
    int val1;
    int val2;

public:
    CTempValue(int v1 = 0, int v2 = 0);
    CTempValue(const CTempValue& t):val1(t.val1),val2(t.val2)
    {
        cout << "调用了拷贝构造函数" << endl;
    }

    CTempValue & operator=(const CTempValue *tmv)
    {
        val1 = tmv->val1;
        val2 = tmv->val2;
        cout << "调用了拷贝赋值运算符" << endl;
        return *this;
    }

    virtual ~CTempValue()
    {
        cout << "调用了析构函数" << endl;
    }

public:
    int Add(CTempValue &ts);  // 普通函数


};

CTempValue::CTempValue(int v1 /* = 0 */, int v2 /* = 0 */):val1(v1), val2(v2)
{
    
    cout << "调用了构造函数" << endl;
    cout << "val1 = " << v1 << endl;
    cout << "val2 = " << v2 << endl;
}
int CTempValue::Add(CTempValue &ts)
{
    int tmp = ts.val1 + ts.val2;
    ts.val1 = 1000;  // 这里修改对外界没有影响
    return tmp;
}

CTempValue Double(CTempValue & ts)
{
    //CTempValue tmp;
    //tmp.val1 = ts.val1 * 2;
    //tmp.val2 = ts.val2 * 2;
    //return tmp;
    return CTempValue(ts.val1 * 2, ts.val2 * 2);
}

class mynum
{
public:
    int num1;
    int num2;

};

mynum operator+(mynum &tmpnum1, mynum &tmpnum2)
{
    mynum result;
    result.num1 = tmpnum1.num1 + tmpnum2.num2;
    result.num2 = tmpnum2.num2 + tmpnum2.num2;

    return result;

}



// 统计字符ch在字符串中出现的次数
int calc(const string &strsource, char ch)
{
    const char *p = strsource.c_str();
    int icount = 0;

    // ......

    return icount;
}


namespace temp
{
    int main()
    {
        // 一：临时对象的概念
        // 另外一些临时对象，是因为我们书写代码问题而产生的


        // 二：产生临时对象的情况和解决，三种情况和解决方案
        // (2.1)以传值的方式给函数传递参数
        //CTempValue tm(10, 20);  // 调用构造函数
        //int sum = tm.Add(tm);  // 这个会导致拷贝构造函数的执行
        //cout << "sum = " << sum << endl;
        //cout << "val1 = " << tm.val1 << endl;

        // (2.2)类型转换生成临时对象/隐式类型转换以保证函数调用成功
        /*CTempValue sum;
        sum = 1000; */ // 这里产生了一个真正的临时对象
        // (1)用1000这个数字创建了一个类型为CTempValue的临时对象
        // (2)调用拷贝赋值运算符把这个临时对象里面的成员赋值给sum对象，
        // (3)销毁这个临时创建的CTempValue
        //CTempValue sum = 1000;  // 把定义对象和给对象初值放在一行
        // 为sum预留空间，用1000构造sum对象，而且是直接构造在sum对象的预留空间里。

        // (2.2)隐式类型转换以保证函数调用成功
        //char mystr[100] = "I love China";
        //int result = calc(mystr, 'o');
        // C++语言只会为const 引用产生临时变量，而不会为非const引用产生临时变量。


        // (2.3)函数返回对象的时候
        CTempValue ts(10, 20);
        //Double(ts);  // 因为返回临时对象导致占用了一个拷贝构造函数和一个析构函数
        CTempValue ts3 = Double(ts);
        CTempValue &&ts4 = Double(ts);  // 临时对象是一种右值

        // Double函数引起的消耗
        // CTempValue tmpm:会消耗一个构造函数和一个析构函数
        // return tmpm:产生临时对象，占用一个拷贝构造函数和析构函数

        // 在举一例：介绍知识点，类外运算符重载
        mynum tm1;
        mynum tm2;


        mynum tm3 = tm1 + tm2;

        // (1)代码优化
        // (2)积累经验

        return 0;
    }

}