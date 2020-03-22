
#include <iostream>
#include <thread>
#include <cassert>
#include "add.h"
#include "mutex_.h"
#include "condition_.h"

#include "async_.h"
#include "async_test.h"
#include "atomic_.h"
#include "atomic_pro.h"
#include "windows_.h"
#include "conditon_pro.h"
#include "43_basic.h"
#include "44_start.h"
#include "45_pass.h"
void do_background_work() {}
int main()
{
    //std::thread t(do_background_work);
    //t.detach();
    //assert(!t.joinable());
    //std::cout << std::this_thread::get_id();

    //add::function();
    //mutex_::func();
    //condition_::func();
    //async_::func();
    //async_test::func();
    //atomic_::main();
    //atomic_pro::main();
    //windows_::main();
    //condition_pro::main();
    //start_::main();
    pass::main();

}