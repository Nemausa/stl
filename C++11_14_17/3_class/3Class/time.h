//////////////////////////////////////////////////////////////////////////
//  @file     add.h
//  @author   Morris
//  @date     2019-03-01
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-03-01
//  -added 
//  @remark   多线程求和
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef TIME_H
#define TIME_H

#include <iostream>
using namespace std;

class TempClass
{
public:
    TempClass()
    {
        cout << "调用了TempClass类的构造函数" << endl;
    }

    TempClass(TempClass& t)
    {
        cout << "调用了TempClass类的拷贝构造函数" << endl;
    }
};


class Time
{
private:
    int milliseconds_;

    void initMillTime(int mill);
public:
    int hour_;
    int minute_;
    int second_ = 0;
 
    TempClass tc;
    mutable int mutable_value_;
    //const int const_value_;  // 定义个常量
public:
    void initTime(int hour, int minute, int second=30);
    // 构造函数
    explicit Time(int hour, int minute, int second);
    Time(int hour);
    Time();
    ~Time();

public:
    void addhour(int hour) const;
    Time& add(int hour);
    static int static_value_;  // 声明静态成员变量，还没有分配内存，所以不能再这里初始化
    static void static_fun();

    // 拷贝构造函数
    Time(const Time &t);

    Time & operator=(const Time&);  // 重载赋值运算符

};

void PrintTime(Time &t);


#endif