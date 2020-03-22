//////////////////////////////////////////////////////////////////////////
//  @file     myvector.h
//  @author   Morris
//  @date     2019-03-18
//  @mail     tappanmorris@outlook.com
//
//  @version  2019-03-18
//  -added 
//  @remark   
//  @note
//////////////////////////////////////////////////////////////////////////

#ifndef MYVECTOR_H
#define MYVECTOR_H

template<typename T>
class myvector
{
public:
    typedef T *myiterator; // 迭代器

public:
    myvector();  // 构造函数

    myvector& operator=(const myvector&);  // 运算符重载，在类模板内部使用模板名并不需要提供模板参数

    myiterator mybegin();
    myiterator myend();
    void myfunc();

};

template<typename T>
void myvector<T>::myfunc()
{
    return;
}

template<typename T>
myvector<T>::myvector()
{

}

template<typename T>
myvector<T>& myvector<T>::operator=(const myvector&)
{
    return *this;
}

template<typename T>
typename myvector<T>::myiterator myvector<T>::mybegin()
{

}

#endif