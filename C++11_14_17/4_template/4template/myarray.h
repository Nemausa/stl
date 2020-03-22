//////////////////////////////////////////////////////////////////////////
//  @file     myarray.h
//  @author   Morris
//  @date     2019-03-18
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-03-18
//  -added 
//  @remark   
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef MYARRAY_H
#define MYARRAY_H

#include <iostream>

template<typename T, int size = 10>
class myarray
{
private:
    T arr[size];
public:
    void myfunc();
};

template<typename T, int size = 10>
void myarray<T, size>::myfunc()
{
    std::cout << size << std::endl;
}




#endif