
/// \ 可变参模板续、模板模板参数
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
#include <unordered_set>
#include <functional>
#include <queue>

using namespace std;
//
namespace _nmsp1
{
    //一：可变参类模板
    //（1.1）通过递归组合方式展开参数包
    //组合关系（复合关系）；类A和类B之间就是一种组合关系
    class B
    {
    public:
        //....
    };
    class A
    {
    public:
        B b; //A中包含B对象
    };


    template<typename...Args> class myclasst {}; //主模板
    template<> class myclasst<>  //0个模板参数的特化版本
    {
    public:
        myclasst()
        {
            printf("myclasst<>::myclasst()执行了,this = %p\n", this);
        }
    };

    template <typename First, typename... Others>
    class myclasst<First, Others...> //: private myclasst<Others...> //偏特化
    {
    public:
        myclasst() :m_i(0)
        {
            printf("myclasst::myclasst()执行了,this = %p\n", this);
        }
        myclasst(First parf, Others...paro) :m_i(parf), m_o(paro...) //, myclasst<Others...>(paro...)
        {
            cout << "-------------------begin----------------" << endl;
            printf("myclasst::myclasst(parf,paro)执行了,this = %p\n", this);
            cout << "m_i=" << m_i << endl;
            cout << "-------------------end------------------" << endl;
        }
        First m_i;
        myclasst<Others...> m_o; //组合关系（复合关系）
    };

    void func()
    {
        myclasst<int, float, double> myc(12, 13.5f, 23); //《c++对象模型探索》



    }
}
namespace _nmsp2
{
    //一：可变参类模板
    //（1.2）通过tuple和递归调用展开参数包
    //这种展开参数包的方式需要写类的特化版本，有一定难度；
    //实现思路：计数器从0开始，每处理一个参数，计数器+1，一直到把所有参数处理完。最后搞一个模板片特化，作为递归调用结束;

    //（1.3）总结
    //获取参数包里参数的方式有很多种；一般都离不开递归手段



    //mycount用于统计，从0开始，mymaxcount表示参数数量
    template<int mycount, int mymaxcount, typename...T>
    class myclasst
    {
    public:
        static void mysfunc(const tuple<T...>&t)
        {
            cout << "value = " << get<mycount>(t) << endl;
            myclasst<mycount + 1, mymaxcount, T...>::mysfunc(t); //递归调用
        }
    };
    //需要有一个特化版本，用于结束递归调用
    template <int mymaxcount, typename...T>
    class myclasst< mymaxcount, mymaxcount, T...>
    {
    public:
        static void mysfunc(const tuple<T...>&t)
        {

        }
    };

    template <typename...T>
    void myfunct(const tuple<T...>&t)  //可变参函数模板
    {
        myclasst<0, sizeof...(T), T...>::mysfunc(t);
    }

    void func()
    {
        tuple<float, int, int> mytuple(12.5f, 100, 52); //一个tuple(元组)：一堆各种东西的组合
                                                        /*cout << get<0>(mytuple) << endl;
                                                        cout << get<1>(mytuple) << endl;
                                                        cout << get<2>(mytuple) << endl;*/
        myfunct(mytuple);
    }
}
namespace _nmsp3
{
    //二：模板 模板参数:这表示 这是个 模板参数， 这个模板参数本身，又是 一个模板；
    //本章 五节：using定义模板别名
    template <
        typename T,    //类型模板参数
                       //template<class> class Container  //这就是一个模板 模板参数
        template<typename W> typename Container
        //typename Container
    > //T,U：叫模板参数 ，因为他们前边都有typename，所以又称为  类型 模板参数
    class myclass
    {
    public:
        T m_i;
        Container<T> myc; //Container作为一个类模板来使用的（因为他屁股后边带着<T>），所以它是个类模板；
                          //大家要明白，如果你要想把Container当成一个类模板来用，你就必须把他弄成“模板模板参数”这种写法；
        myclass()
        {
            for (int i = 0; i < 10; ++i)
            {
                myc.push_back(i);
            }
        }
    };

    template<typename T> using MYVec = vector<T, allocator<T>>;  //这种套路，写法很固定
    template<typename T> using MYList = list<T, allocator<T>>;  //这种套路，写法很固定


    void func()
    {
        //vector<int> myvector;
        //myclass<int, vector> myvecobj; //本意是往容器中塞入元素，元素类型为int
        myclass<int, MYVec> myvecobj;
        myclass<int, MYList> mylistobj;


    }
}











