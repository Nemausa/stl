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


class OtherClass
{
public:
    OtherClass(int n) {};
};

class Time2
{
private:
    int milliseconds_;
   
public:
    int hour_;
    int minute_;
    int second_ = 0;
    OtherClass oc;

    mutable int mutable_value_;
    const int const_value_=10;  // 定义个常量
public:

    //Time2() = default;  
    //Time2() = delete;  // 让程序化显示的禁用某个函数

};




#endif