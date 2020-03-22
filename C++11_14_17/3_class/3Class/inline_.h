#pragma once

#include "time.h"
#include <iostream>
using namespace std;


namespace inline_
{


    int main()
    {
        // 一：在类定义中实现成员函数inline：类内的成员函数实现其实也叫类内的成员函数定义
        // 这种直接在类的定义中实现的函数，会被当做inline内联函数处理。

        // 二：成员函数末尾的const
        // const:常量，在成员函数末尾增加一个const。不但要在成员函数声明中增加，也要在成员函数的定义增加const
        // 作用：告诉系统，这个成员函数不会修改对象里任何成员变量的值等等。也就是说，这个成员函数不会修改类Time的任何状态。
        // 末尾加const后缀的成员函数，“常量成员函数”

        const Time abc;  // 定义const对象，这种对象有限制。
        //abc.initTime(1, 2);  // 只能调用const函数，initTime只能被非const对象调用。

        // const函数，则不管const对象还是非const，都可以调用const成员函数。
        // 而非const函数，只能被非常const对象，不能被const对象调用。

        // 三：mutable（不稳定，容易改变的意思），const的反义词.mutable的引入也正好是为了突破const的限制
        // 用这个mutable修饰一个成员变量，一个成员变量一旦被mutable修饰了，就表示这个变量
        // 永远处于可被修改的状态，即便是在const结尾的成员函数中也可以修改。

        // 四：返回自身对象的引用，this
        // 如何理解这个this，咱们调用成员函数时，编译器负责把这个对象的地址传递给成员函数一个隐藏的this形参。
        // 在系统角度看来，任何对类成员的直接访问都是通过this的隐式调用。
        // (a)this指针只能在成员汗水中使用，全局函数，静态函数都不能使用this指针。
        // (b)在普通成员函数中，this是一个指向非const对象的const指针（类型为Time，
        // 那么this就是 Time* const this）表示this只能指向当前的Time对象。
        // （c)在const成员函数中，this指针是一个指向const对象的const指针（类型为Time,this也就是const Time *const this);


        // 五:static成员
        // 有属于整个类的成员变量，这种成员变量就叫static成员变量。
        // 特点：不属于某个对象，属于整个类，我们一旦在某个对象中修改了整个成员变量的值，在其他的对象中也能够看到修改的结果。
        // 这种成员变量只有一个副本，对于这种成员变量的引用，我们用的是类名::成员变量名
        // 成员函数前面也可以加static构成静态成员函数，属于整个类的成员函数，调用时类名::成员函数名
        // 如何定义静态成员变量，我们一般会在某个.cpp源文件中的开头来定义这个静态成员变量。
        // 这样的话就能保证在调用任何函数之前保证这个变量已经被初始化。
        Time t;
        t.add(10);
        return 0;
    }


}

