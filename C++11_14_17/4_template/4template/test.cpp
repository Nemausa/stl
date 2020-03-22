#include <iostream>
using namespace std;
#include "ca.h"

// 显示实例化  手段中的 实例化定义，这种实例化定义只需要在一个.cpp文件中就可以
template A<float>;  // 编译器遇到这段代码就直接实例化出来一个 A<float>
template void myfunc(int v1, int v2);  // 编译器也会为其生成代码


void mfunc()
{
    A<float> a(1, 2);
}

