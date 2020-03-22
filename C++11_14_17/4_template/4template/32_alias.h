//////////////////////////////////////////////////////////////////////////
//  @file     alias.h
//  @author   Morris
//  @date     2019-03-20
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-03-20
//  -added 
//  @remark   using定义模板别名，显示指定模板参数
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef ALIAS_H
#define ALIAS_H
#include <iostream>
#include <string>
#include <map>

namespace alias
{

    // 希望定义一个类型，前边这部分固定不变，std::map<std::string, 类型自己指定>
    // C++98
    template<typename wt>
    struct map_s
    {
        typedef std::map<std::string, wt> type;
    };

    // C++11
    template<typename T>
    using str_map_t = std::map<std::string, T>;  // str_map_t是类型别名
    // using用来给"类型模板"起名字的作用

    template<typename T>
    using myfunc_M = int(*)(T, T); // 定义类型模板 是个函数指针模板

    int RealFunc(int a, int b)
    {
        return 1;
    }

    template<typename T1, typename T2, typename T3>
    T1 sum(T2 a, T3 b)
    {
        T1 result = a + b;
        return result;
    }

    int main()
    {
        // 一：using定义模板别名
        // typedef:一般用来定义类型别名
        typedef unsigned int unit_t;  // 相当于给unsigned int类型起了一个别名unit_t
        unit_t abc;
        typedef std::map<std::string,int> map_s_i;
        map_s_i mymap;
        mymap.insert({ "first", 1 });
        map_s<int>::type map1;
        map1.insert({ "first", 1 });

        str_map_t<int> map2;
        map2.insert({ "first", 1});

        // using在用于定义类型(定义类型模板)的时候，包含了typedef的所有功能
        typedef unsigned int unit_t;
        using unit_t = unsigned int;

        typedef int(*FuncType)(int, int);  
        using FuncType = int(*)(int, int);

        myfunc_M<int> pointFunc; 
        pointFunc = RealFunc;
        cout << pointFunc(1, 2) << endl;;

        // 总结：
        // using中使用这种模板，既不是类模板，也不是函数模板，我们可以看成是一种新的模板类型：类型模板(模板别名)

        // 二：显示指定模板参数
        auto result = sum<long long, long long, long long>(2000000000, 2000000000);
        cout << result << endl;
  
        return 0;
    }

}




#endif