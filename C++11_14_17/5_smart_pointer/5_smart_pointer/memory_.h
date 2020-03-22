//////////////////////////////////////////////////////////////////////////
//  @file     memory_.h
//  @author   Morris
//  @date     2019-03-06
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-03-06
//  -added 
//  @remark   直接内存管理、创新新工程观察内存泄漏
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef MEMORY_H
#define MEMORY_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

namespace memory_
{
    void myfunc()
    {
        int i;
        i = 5;
        static int j; // 局部静态对象
    }

    void main()
    {
        // 一：直接内存管理（new/delete）
        // new分配方式称之为动态分配，分配在堆上，直接内存管理
        // 如何初始化
        //int *pointi = new int; // 初值未定义
        //int *point2 = new int(100);  // 用圆括号给一个int的动态对象初值
        //string *string1 = new string(5, 'a');
        //vector<int> *poinv = new vector<int>{ 1,2,3,4,5 };

        //// 概念“值初始化”：用（）来初始化
        //string *str = new string();  // 也是空字符串
        //int *point3 = new int();  // 值初始化发现变成了0
        // 类是否是值初始化效果一样，都是调用直接的构造函数
        // new对象的时候，能够进行"值初始化"就进行一下为好，防止它的值没有被初始化
        // C++11中，auto可以和new配合使用
        string *string1 = new string(5, 'a');
        auto string3 = new auto(string1);
        cout << string1->c_str() << endl;
        cout << (*string3)->c_str() << endl;

        // const 对象也可以动态分配
        const int *pointci = new const int(200);

        // new和delete说明：
        // (a)成对使用，delete是回收用new分配的内存(释放内存)，不是new出来的内存，不能用delete释放
        // (b)delete一块内存，只能delete一次，不能delete多次。空指针可以删除多次，但删除多次没有什么意义。
        int i = 12;
        int *p = &i;
        delete p;  //*不是new出来的对象不能delete，否则执行会报告异常


        // 注意事项总结：
        // (1)new出来的千万不要忘记delete，否则内存泄漏，时间一长导致系统资源紧张，运行崩溃
        // (2)delete后的内存不能再使用，否则异常。
        // (3)同一块内存释放两次的问题；也会报异常
        // 用new和delete直接进行内存管理，要很小心；
        // C++11开始出现"智能指针"

        // 二：创建新工程，观察内存泄漏
        // MFC应用程序能在一定的程度上（程序退出的时候),能够帮助我们发现内存泄漏；


    }



}



#endif
