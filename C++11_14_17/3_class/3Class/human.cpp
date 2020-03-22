#include "human.h"
#include <iostream>
using namespace std;



// 实现
Human::Human()
{
    cout << "执行了Human::Human()" << endl;
}

Human::Human(int age):age_(age)
{

}

void Human::eat()
{
    cout << "吃各种粮食" << endl;
}

Human::~Human()
{
    cout << "Human::~Human()" << endl;
}

