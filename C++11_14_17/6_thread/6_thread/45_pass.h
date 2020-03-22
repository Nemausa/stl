#pragma once
#include <iostream>
#include <thread>
using namespace std;

class PA
{
public:
    int i_;
    PA(int a) :i_(a) { cout << "PA构造函数" << this << "threadid = " << this_thread::get_id() << endl;; }
    PA(const PA & a) :i_(a.i_) { cout << "PA拷贝构造函数" << this << "threadid = " << this_thread::get_id()<< endl; }
    ~PA() { cout << "PA析构函数"  << this << "threadid = " << this_thread::get_id() << endl; }
    void thread_work(int num)
    {
        cout << "子线程threadwork执行了" << endl;
    }

    void operator()(int num)
    {
        cout << "子线程()执行 " << "this id = " << this_thread::get_id() << endl;
    }

};


namespace pass
{

    //void myprint(const int &i, char *p)
    void myprint(const int &i, const string &buf)
    {
        cout << i << endl;  // 分析认为，i并不是mavary的引用，实际是值传递，即便主线程detach了子线程，那么子线程中用这个i值仍然是安全的。
        cout << buf.c_str() << endl;  // 指针在detach子线程，绝对有问题
    }

    void printPA(const int i, const PA &a)
    {
        cout << &a << endl;
    }

    void pirnt2(PA &pa)
    {
        pa.i_ = 100;
        cout << "子线程的参数地址是" << &pa << "this id = " << this_thread::get_id() << endl;
    }

    void print3(unique_ptr<int> p)
    {

    }

   

    int main()
    {
		/*  一：传递临时对象作为线程参数
		  (1.1)要避免的陷阱
		  事实1：只要用临时对象作为参数传递给线程，那么久一定能够在主线程执行完毕前把线程的第二个参数构建出来，从而确保即便detach了，也是安全的。
		  (1.3)总结
		  a)如果传递int这种简单类型参数，建议都是值传递，不要用引用，防止节外生枝。
		  b)如果传递类对象，避免隐式类型转换。全部都在创建线程这一行就构建出临时对象来，然后在函数参数里，用引用来接，否则系统还会构造一次对象，浪费。
		  终极结论：建议不适用detach，只是用join，这样就不存在局部变量失效导致线程对内存的非法引用问题。

		  二：临时对象作为参数继续讲
		  (2.1)线程id概念:id是个数字，每个线程(不管是主线程还是子线程)实际上都对应着一个数字，而且每个线程对应的数字都不同。
		  也就是说不同的线程，它的线程id必然不同
		  线程id可以用C++标准库里的函数来获取，std::this_thread::get_id()来获取
		  (2.2)临时对象构造时机捕获

		  三：传递类对象，智能指针作为参数
		  std::ref()函数

		  四：用成员函数指针做线程函数*/

        int myvar = 1;
        int &mvary = myvar;

        char buf[] = "this is a test";
        thread obj(myprint, mvary, buf);  // 但是buf在什么时候转成string的
        // 事实上存在，buf被回收了，系统才用buf转成string
        thread obj(myprint, myvar, string(buf));  // 我们这里直接将buf转成string对象，这是一个可以保在证线程中肯定有效
        obj.join();


        int var = 1;
        int secondvar = 12;
        thread obj(printPA, var, static_cast<PA>(secondvar));  // 我们希望secondvar转成PA对象传递给printPA的第二个参数
        // 在创建线程的同时构造临时对象的方法传递参数是可用的
        obj.join();
        obj.detach();

        cout << "主线程id " << this_thread::get_id() << endl;
        int var = 1;
        thread obj2(pirnt2, static_cast<PA>(var));
        obj.join();

        PA pa(10);
        thread obj3(pirnt2, std::ref(pa));
        obj.join();

        unique_ptr<int> p(new int(100));
        thread obj4(print3, std::move(p));

        PA pa(10);
        thread obj5(&PA::thread_work, pa, 15);
        obj5.join();

        PA pa(10);
        thread obj6(std::ref(pa), 5);  // 不再调用拷贝构造函数了，那么后续如果调用detach就不安全了
        obj6.join();
        cout << "I love China" << endl;

        return 0;
    }
}