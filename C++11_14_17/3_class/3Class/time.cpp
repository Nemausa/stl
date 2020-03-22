#include "time.h"
#include <iostream>
using namespace std;


int Time::static_value_ = 0; // 可以不给初值，系统默认时给0，定义是不需要static

void PrintTime(Time &t)
{
    cout << t.hour_ << endl;
}

//其中::是作用域运算符，表示initTime函数Time类
void Time::initTime(int hour, int minute, int second)
{
    hour_ = hour;  // 我们注意到，成员函数中，我们可以直接使用成员变量名
    // 哪个对象调用该成员函数，这些成员变量就属于哪个对象，大家可以理解类成员函数知道哪个对象调用直接
    minute_ = minute;
    second_ = second;
}


void Time::initMillTime(int mill)
{
    milliseconds_ = mill;
}

Time::Time(int hour, int minute, int second)
    :hour_(hour), minute_(minute), second_(second), milliseconds_(0)/*,const_value_(8)*/
{
    //hour_ = hour;               
    //minute_ = minute;
    //second_ = second;

    cout << "调用了Time(int,int, int)构造函数" << endl;
}

Time::Time(int hour)/*:const_value_(8)*/
{
    hour_ = hour;
    minute_ = 59;
    second_ = 59;

    cout << "调用了Time(int)构造函数" << endl;
}

Time::Time() /*:const_value_(8)*/
{
    hour_ = 12;
    minute_ = 59;
    second_ = 59;

    cout << "调用了Time函数" << endl;
}

void Time::addhour(int hour) const
{
    //minute_ = hour;
    mutable_value_ = 10;
}

Time& Time::add(int hour)
{
    hour_ += hour;
    return *this;  // 把对象自己给返回了
}

void Time::static_fun()
{

}

Time::Time(const Time &t):hour_(20), minute_(20)
{
    cout << "调用了Time::Time(const Time &t)拷贝构造函数" << endl;
}

Time & Time::operator=(const Time &t)
{
    cout << "调用了Time::operator=" << endl;
    return *this;
}

Time::~Time()
{
    cout << "调用了析构函数" << endl;
}