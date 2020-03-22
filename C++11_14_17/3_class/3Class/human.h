//////////////////////////////////////////////////////////////////////////
//  @file     human.h
//  @author   Morris
//  @date     2019-03-03
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-03-03
//  -added 
//  @remark   父类
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
using namespace std;

class Human
{
public:
    Human();
    Human(int);
    virtual ~Human();
public:
    int age_;
    char name_[100];
    void public_fun() {}
    virtual void eat();
    virtual void eat2() = 0; // 纯虚函数，没有函数体，只有函数声明。
    
    Human & operator=(const Human &t)
    {
        return *this;
    }
protected:
    int protected_value_;
    void protected_func() {}

private:
    int private_value;
    void private_func() {}
};


#endif