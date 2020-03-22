#pragma once
#include <thread>
void do_something(int i)
{
}

struct func
{
    int& i;
    func(int& i_) : i(i_) {}
    void operator() ()
    {
        for (unsigned j = 0; j < 1000000; ++j)
        {
            do_something(i); // 1. 潜在访问隐患：悬空引用
        }
    }
};

void do_something_in_current_thread() {}
struct func; // 定义在清单2.1中
void f()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    try
    {
        do_something_in_current_thread();
    }
    catch (...)
    {
        t.join(); // 1
        throw;
    }
    t.join(); // 2
}

class thread_guard
{
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_) :
        t(t_)
    {}
    ~thread_guard()
    {
        if (t.joinable()) // 1
        {
            t.join(); // 2
        }
    }
    thread_guard(thread_guard const&) = delete; // 3
    thread_guard& operator=(thread_guard const&) = delete;
};

void f2()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
    do_something_in_current_thread();
}

//void update_data_for_widget(widget_id w, widget_data& data); // 1
//void oops_again(widget_id w)
//{
//    widget_data data;
//    std::thread t(update_data_for_widget, w, std::ref(data)); // 2
//    display_status();
//    t.join();
//    process_widget_data(data); // 3
//}