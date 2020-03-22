﻿#pragma once
#include <iostream>
using namespace std;
#include "human.h"
#include "men.h"
#include "women.h"

namespace final_
{

    int main()
    {
        // 一：基类指针，派生类指针
        ///*Human *phuman = new Human;
        //Men *pmen = new Men;*/

        // 新玩法：父类指针可以new一个子类对象。父类指针很强大
        //Human *phuman = new Men;
        //phuman->public_fun();
        //pmen->funcmen();  // 不可以，虽然你new子类对象，但是你是父类指针，无法调用子类成员函数。
        // 既然父类指针没有办法调用子类的成员函数，那么为什么你还可以让父类new一个子类对象，有什么用呢？
        //
        // 二：虚函数
        // 问题：有没有一个解决方法，是我们定义一个对象指针，就能够调用父类，以及各个子类的同名函数？
        // 有：这个对象指针，它的类型必须是父类类型。
        // 我们如果想通过一个父类指针调用父类，子类中的同名函数同参的函数，对这个函数也是有要求的
        // 在父类中，eat函数声明之前必须加virtual声明的eat函数成虚函数。
        // 一旦某个函数在基类中声明成了虚函数，那么所有子类它都是虚函数
        //phuman->eat(); // 调用的是Men的eat函数，
        //phuman->Human::eat();  // 调用基类的eat
        //delete phuman;

        //phuman = new Women;  // 女人喜欢吃面食
        //phuman->eat();
        //delete phuman;

        //phuman = new Human;  // 吃各种粮食
        //phuman->eat();
        //delete phuman;
        //
        // 为了避免你在子类中写错虚函数，在C++11中，你可以在函数声明中增加一个override关键字，
        // 这个关键字用在"再来"中，而且是虚函数专用。
        // override就是用来说明派生类中的虚函数，你用了这个关键字之后，编译器就会认为你这
        // 个eat是覆盖了父类中的同名函数（只有虚函数才可以在子类覆盖父类中同名函数问题）
        // 那么编译器就会在父类中找同名同参的虚函数，如果没有找到，编译就报错。

        // final也是虚函数专用，是用在"父类"，如果我么在父类的函数声明中加了final，那么任何尝试覆盖该函数的操作都将引发错误。
        // 调用虚函数执行的是动态绑定，"动态"：表示的就是我么在程序运行的时候才知道调用哪个子类的虚函数。
        // 动态绑定：运行的时候才能决定你的对象绑定到哪个函数上运行了。

        // 三：多态性
        // 多态性只是针对虚函数来说的；
        // 随着虚函数的提出，面向对象编程里面有个概念"多态性",就付出水面。
        // 多态性：体现在具有继承关系的父类和子类之间，子类重定义父类的成员函数，同时父类中函数声明成了virtual虚函数。
        // 通过父类指针，只有到了程序运行时期，找到了动态绑定到父类指针的对象，这个对象它有可能是某个子类对象，也可能是父类，
        // 然后系统内部实际要查一个虚函数标，找到了函数入口地址，从而调用父类或者子类的函数，这就是运行时期的多态性。

        // 四：纯虚函数
        // 纯虚函数是在基类中声明的函数，但是他在基类中没有定义，但是要求任何派生类都要定义该函数自己的实现方法。
        // 基类中实现纯虚函数的方法就是在函数原型后面增加=0；
        // 大家注意，一旦一个类中有了纯虚函数，那么你就不能生成这个类的对象了，这个类成为了"抽象类";
        // 抽象类不能用来生成对象，主要目的用来统一管理子类对象
        //Human human;

        // 所以大家记住2点
        // (1)函数纯虚函数的类叫抽象类，不能用来生成该对象，主要用于当做基类生成子类用的。
        // (2)子类中必须事项该基类中定义的纯虚函数。

        // 五：基类的虚构函数一般写成虚函数
        //Human *phuman = new Men;
        //delete phuman;  // 没有执行子类的析构函数
        // 结论：用基类指针new子类独享，在delete的系统不会调用派生类的析构函数，这肯定有问题。
        // 如果把父类的析构函数写成虚函数
        // 大家记住：在public基础中，基类对派生类对其对象操作，只能影响那些从基类继承下来的成员。
        // 如果想用基类对非继承成员进行操作，则要把基类的这个函数定义为虚函数，析构函数自然应该如此。
        // 另外就是基类中析构函数的虚属性也会被继承给子类，这样的话子类中析构函数也就自然而然成为虚函数了，虽然名字和基类析构函数不一样。
        // delete phuman的时候肯定要调用父类的析构函数，但在父类析构函数中它要是想要调用子类Men中的析构函数，那么
        // Hunam这个类的析构函数必须声明为virtual,也就是说C++中为了或得运行时的多态行为，所调用的成员函数必须是virtual。

        // 所以大家要记住结论
        // 如果一个类，想要做基类，那么务必把这个类的析构函数写成virtual析构函数。
        // 只要基类的析构函数是虚函数，就能够保证我们delete基类指针能够运行正确的析构函数版本。

        // 普通类我们可以不写析构函数，如果是基类，就必须写一个析构函数，而且这个析构函数还必须是virtual析构函数。
        // 虚函数会增加内存开销的，类里面定义虚函数，编译器就会给这个类增加虚函数表，在这个表里存放虚函数指针。
        return 0;
    }
}