
#include <iostream>
using namespace std;
#include "project1.h"
#include "project2.h"
#include "inline_.h"
#include "default_.h"
#include "copy_.h"
#include "men.h"
#include "final_.h"
#include "friend_.h"
#include "RTTI_.h"
#include "derived.h"
#include "temp.h"
#include "move2.h"
#include "MultiInherit.h"
#include "convert.h"
static int g_abc = 5;  // 存储在静态存储区，限制该全局变量只能够用在本文件中。

int main()
{
    //class_::main();
    //class2_::main();
    //inline_::main();
    //default_::main();
    //copy_::main();

    //final_::main();
    //friend_::main();
    //RTTI_::main();
    //derived_::main();
    //temp::main();
    //move2::main();
    //multi::main();
    convert::main();



}