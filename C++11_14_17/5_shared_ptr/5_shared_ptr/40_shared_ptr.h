#pragma once

#include <iostream>
using namespace std;

#include <memory>

class CT : public enable_shared_from_this<CT>
{
public:
    shared_ptr<CT> getself()
    {
        //return shared_ptr<CT>(this);  // 用裸指针初始化多个shared_ptr的感觉
        return shared_from_this();

    }
};
class CB;
class CA
{
public:
    shared_ptr<CB> m_pbs;
    ~CA()
    {
        int test;
        test = 1;
    }
};

class CB
{
public:
    //shared_ptr<CA> m_pas;
    weak_ptr<CA> m_pas; 
    ~CB()
    {
        int test;
        test = 1;
    }
};



namespace shared2
{

    shared_ptr<int> create(int value)
    {
        return make_shared<int>(value);
    }

    shared_ptr<int> myfunc(int value)
    {
        shared_ptr<int> ptmp = create(value);
        return ptmp;
    }

    void proc(shared_ptr<int>)
    {
        return;
    }
    void main()
    {
        //auto p1 = myfunc(10);// 这块如果不用一个shared_ptr变量来接受返回结果，那么返回的shared_ptr也会被销毁,所指向的对象也会被销毁


        // std::shared_ptr使用陷阱分析
        // (2.1)慎用裸指针
        //int *p = new int(100);
        //proc(p);  // 语法 错，int*p不能转换成shared_ptr<int>
        //proc(shared_ptr<int>(p));  // 参数是个临时的shared_ptr，用一个裸指针显示的构造
        //*p = 45; // 出现潜在的不可预料的问题，因为p指向的内存已经被释放

        // 把一个普通裸指针绑定到一个shared_ptr上之后，那么内存管理的责任就交给shared_ptr了，这个时候就
        // 不应该用裸指针来访问shared_ptr所指向的内存
        // 绝对要记住不要用裸指针初始化多个shared_ptr

        //int *p = new int(100);  // 裸指针
        //shared_ptr<int> p1(p);
        //shared_ptr<int> p2(p);  // p1和p2无关联(p1和p2的强引用计数都为1)，会导致p1和p2所指向的内存释放两次


        // (2.2)慎用get返回的指针
        // 返回智能指针所指向的对应的裸指针（有些函数接口可能只能使用裸指针）
        // get返回的指针不能delete，否则会异常
        //shared_ptr<int> p(new int(100));
        //int *pp = p.get();
        //delete pp;  // 不能删除，会导致异常
        // 不能将get返回的指针绑到其他智能指针上
        {
          //  shared_ptr<int> p2(pp);
        }
        // 离开了这个作用域，导致指向的内存被释放
        //*p = 56;  // 该内存已经释放，这样的赋值会导致不可预料的结果
        // 结论：永远不要用get得到的一个指针初始化另一个智能指针或这个给另外一个智能指针赋值。
        

        // (2.3)不要用类对象指针(this）作为shared_ptr返回，改用enable_shared_form_this

        //shared_ptr<ct> pct1(new ct);
        // shared_ptr<ct> pct2 = pct1;  // 这是两个强引用
        //shared_ptr<ct> pct2 = pct1->getself();  // 问题出现
        // 用c++标准库里面的类模板：enable_shared_from_this
        // 现在在外面创建ct对象的智能指针以及通过ct对象返回的this智能指针都是安全的
        // 这个enbale_shared_from_this中有个弱指针weak_ptr，这个弱指针能够监视this
        // 在我们调用shared_from_this()这个方法是，这个方法内部实际上是调用这个weak_ptr的lock方法。
        // 大家都知道lock()方法会让shared_ptr引用计数加1，同时返回这个shared_ptr，这个就是工作原理
        

        // (2.4)避免循环引用：导致内存泄漏
        //shared_ptr<ca> pa(new ca);
        //shared_ptr<cb> pb(new cb);
        //pa->m_pbs = pb;  // 等价于指向cb的对象有两个强引用
        //pb->m_pas = pa;  // 1.等价于指向ca的对象有两个强引用  2.因为m_pas是弱引用，这里指向ca的对象只有一个强引用
        //// 离开作用域之后，pca引用计数从1变成0会释放ca对象（caca析构函数执行）
        // ca的析构函数被执行，表示对象即将被释放，导致ca内的m_pbs引用计数减1
        // 也就是指向cb的对象引用计数减1，超出pb作用域指向cb的引用计数也会减1，指向cb对象的引用计数会从1到0，导致cb对象被释放
        // ca先析构，


        // 三：性能说明
        // shared_ptr的尺寸是裸指针的两倍， weak_ptr也是裸指针的两倍
        // (a)第一个裸指针指向这个智能指针所指向的对象
        // (b)第二个裸指针指向一个很大的数据结构(控制块), shared_ptr引用计数，weak_ptr引用计数 删除器，内存分配器等等
        // 这个控制块是由第一个指向某个对象的shared_ptr来创建

        // 控制块创建的时机
        // (a)make_shared:分配并初始化一个对象，返回指向此对象的shared_ptr，所以make_shared总是能够创建一个控制块
        // (b)用裸指针来创建一个shared_ptr对象时
       /* int *pi = new int();
        shared_ptr<int> p1(pi);
        shared_ptr<int> p2(pi); */// 不允许，否则会产生多个控制块，也就是多个引用计数，析构多次


        // (3.2)移动语义
        //shared_ptr<int> p1(new int(100));
        //shared_ptr<int> p2(std::move(p1));  // 移动语义，移动构造一个新的智能指针对象，p1就不在指向该对象了，引用计数依旧是1


        // 四：补充说明和建议
        // (a)掌握了shared_ptr大部分的用法
        // 分配器解决内存分配问题
        // shared_ptr<int> p(new int(), mydelete(), mymallocator());

        // (b)谨慎使用，凡是没有提及的奇怪用法，不要轻易尝试
        // (c)优先使用make_shared(),不能定义自己的删除器
        shared_ptr<string> ps(new string("I Love China")); // 分配两次内存
        auto p2 = make_shared<string>("I Love China"); // 分配一次内存



        return;
    
    }

}