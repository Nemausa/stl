#include "stdafx.h"

// author : Hou Jie (侯捷)
// date : 2015/10/28 
// compiler : DevC++ 5.11 (MinGW with GNU 4.9.9.2)
//
// 說明：這是侯捷 E-learning video "C++標準庫" 的實例程式.
// 該課程的所有測試都出現在此.
// 每一個小測試單元都被放進一個 namespace 中, 
// 如此保持各單元間最大的獨立性.
// 每個 namespace 上方皆有該單元相應的 #include <...> 
// 因此有可能整個程式重複含入 (included) 某些 headers. 
// 這無所謂，因為每個 standard headers 都有自我防衛機制，不讓自己被 included 二次.
//
// 本文件用到若干 C++ 2.0 New Features，所以你必須在你的集成環境 (IDE) 上設定 "C++11 on". 
// 如果你的編譯器報錯，應是因為我用到 (測試) GNU 標準庫的獨特 (非標準) 組件 (特別是 allocators)，
// 將報錯語句改為註解 (comments) 即可通過編譯. 


const long ASIZE = 500000L;

//----------------------------------------------------
#include <iostream>
#include <cstdio>  //snprintf()
#include <cstdlib> //RAND_MAX
#include <cstring> //strlen(), memcpy()
#include <string> 
#include <vector>

using namespace std;
using std::cin;
using std::cout;
using std::string;
//using namespace std;

//以下 MyString 是為了測試 containers with moveable elements 效果.  
class MyString {
public:
    static size_t DCtor;  	//累計 default-ctor 的呼叫次數 
    static size_t Ctor;  	//累計 ctor      的呼叫次數 
    static size_t CCtor;  	//累計 copy-ctor 的呼叫次數 
    static size_t CAsgn;  	//累計 copy-asgn 的呼叫次數 
    static size_t MCtor;  	//累計 move-ctor 的呼叫次數 
    static size_t MAsgn;  	//累計 move-asgn 的呼叫次數 		    
    static size_t Dtor;	//累計 dtor 的呼叫次數 
private:
    char* _data;
    size_t _len;
    void _init_data(const char *s) {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }
public:
    //default ctor
    MyString() : _data(NULL), _len(0) { ++DCtor; }

    //ctor
    MyString(const char* p) : _len(strlen(p)) {
        ++Ctor;
        _init_data(p);
    }

    // copy ctor
    MyString(const MyString& str) : _len(str._len) {
        ++CCtor;
        _init_data(str._data); 	//COPY
    }

    //move ctor, with "noexcept"
    MyString(MyString&& str) noexcept : _data(str._data), _len(str._len) {
        ++MCtor;
        str._len = 0;
        str._data = NULL;  	//避免 delete (in dtor) 
    }

    //copy assignment
    MyString& operator=(const MyString& str) {
        ++CAsgn;
        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _init_data(str._data); 	//COPY! 
        }
        else {
            // Self Assignment, Nothing to do.   
        }
        return *this;
    }

    //move assignment
    MyString& operator=(MyString&& str) noexcept {
        ++MAsgn;
        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _data = str._data;	//MOVE!
            str._len = 0;
            str._data = NULL; 	//避免 deleted in dtor 
        }
        return *this;
    }

    //dtor
    virtual ~MyString() {
        ++Dtor;
        if (_data) {
            delete _data;
        }
    }

    bool
        operator<(const MyString& rhs) const	//為了讓 set 比較大小  
    {
        return std::string(this->_data) < std::string(rhs._data); 	//借用事實：string 已能比較大小. 
    }
    bool
        operator==(const MyString& rhs) const	//為了讓 set 判斷相等. 
    {
        return std::string(this->_data) == std::string(rhs._data); 	//借用事實：string 已能判斷相等. 
    }

    char* get() const { return _data; }
};
size_t MyString::DCtor = 0;
size_t MyString::Ctor = 0;
size_t MyString::CCtor = 0;
size_t MyString::CAsgn = 0;
size_t MyString::MCtor = 0;
size_t MyString::MAsgn = 0;
size_t MyString::Dtor = 0;

namespace std 	//必須放在 std 內 
{
    template<>
    struct hash<MyString> 	//這是為了 unordered containers 
    {
        size_t
            operator()(const MyString& s) const noexcept
        {
            return hash<string>()(string(s.get()));
        }
        //借用現有的 hash<string> (in ...\include\c++\bits\basic_string.h)
    };
}
//-----------------
//以下 MyStrNoMove 是為了測試 containers with no-moveable elements 效果.  
class MyStrNoMove {
public:
    static size_t DCtor;  	//累計 default-ctor 的呼叫次數 
    static size_t Ctor;  	//累計 ctor      的呼叫次數 
    static size_t CCtor;  	//累計 copy-ctor 的呼叫次數 
    static size_t CAsgn;  	//累計 copy-asgn 的呼叫次數 
    static size_t MCtor;  	//累計 move-ctor 的呼叫次數 
    static size_t MAsgn;  	//累計 move-asgn 的呼叫次數 		    
    static size_t Dtor;	    //累計 dtor 的呼叫次數 
private:
    char* _data;
    size_t _len;
    void _init_data(const char *s) {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }
public:
    //default ctor
    MyStrNoMove() : _data(NULL), _len(0) { ++DCtor; _init_data("jjhou"); }

    //ctor
    MyStrNoMove(const char* p) : _len(strlen(p)) {
        ++Ctor;  _init_data(p);
    }

    // copy ctor
    MyStrNoMove(const MyStrNoMove& str) : _len(str._len) {
        ++CCtor;
        _init_data(str._data); 	//COPY
    }

    //copy assignment
    MyStrNoMove& operator=(const MyStrNoMove& str) {
        ++CAsgn;

        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _init_data(str._data); 	//COPY! 
        }
        else {
            // Self Assignment, Nothing to do.   
        }
        return *this;
    }

    //dtor
    virtual ~MyStrNoMove() {
        ++Dtor;
        if (_data) {
            delete _data;
        }
    }

    bool
        operator<(const MyStrNoMove& rhs) const		//為了讓 set 比較大小 
    {
        return string(this->_data) < string(rhs._data);  //借用事實：string 已能比較大小. 
    }

    bool
        operator==(const MyStrNoMove& rhs) const	//為了讓 set 判斷相等. 
    {
        return string(this->_data) == string(rhs._data);  //借用事實：string 已能判斷相等. 
    }

    char* get() const { return _data; }
};
size_t MyStrNoMove::DCtor = 0;
size_t MyStrNoMove::Ctor = 0;
size_t MyStrNoMove::CCtor = 0;
size_t MyStrNoMove::CAsgn = 0;
size_t MyStrNoMove::MCtor = 0;
size_t MyStrNoMove::MAsgn = 0;
size_t MyStrNoMove::Dtor = 0;

namespace std 	//必須放在 std 內 
{
    template<>
    struct hash<MyStrNoMove> 	//這是為了 unordered containers 
    {
        size_t
            operator()(const MyStrNoMove& s) const noexcept
        {
            return hash<string>()(string(s.get()));
        }
        //借用現有的 hash<string> (in ...\4.9.2\include\c++\bits\basic_string.h)
    };
}

//----------------------------------------------------
#include <iostream>
#include <cstdio>  //snprintf()
#include <cstdlib> //RAND_MAX
#include <string> 
#include <algorithm> 
#include <list> 
#include <forward_list> 
using namespace std;
using std::cin;
using std::cout;
using std::string;
using std::max;
using std::min;

namespace jj00
{

    bool strLonger(const string& s1, const string& s2) {
        return s1.size() < s2.size();
    }

    void test_misc()
    {
        cout << "\ntest_misc().......... \n";

        //以下這些是標準庫的眾多容器的 max_size() 計算方式.  
        cout << size_t(-1) << endl;					         	//4294967295
        cout << size_t(-1) / sizeof(long) << endl;		     	//1073741823
        cout << size_t(-1) / sizeof(string) << endl;	         	//1073741823
        //cout << size_t(-1) / sizeof(_List_node<string>) << endl; 	//357913941
        //cout << size_t(-1) / sizeof(_Fwd_list_node<string>) << endl; //536870911
        cout << "RAND_MAX= " << RAND_MAX << endl;	//32767

        cout << min({ 2,5,8,9,45,0,81 }) << endl;  //0
        cout << max({ 2,5,8,9,45,0,81 }) << endl;  //81
        vector<int> v{ 2,5,8,9,45,0,81 };

        cout << "max of     zoo and hello : "
            << max(string("zoo"), string("hello")) << endl;              //zoo
        cout << "longest of zoo and hello : "
            << max(string("zoo"), string("hello"), strLonger) << endl;   //hello    

        cout << hash<MyString>()(MyString("Ace")) << endl;		//1765813650
        cout << hash<MyString>()(MyString("Stacy")) << endl;	//2790324277
        cout << "MyString(zoo) < MyString(hello) ==> " << (MyString("zoo") < MyString("hello")) << endl;	//0
        cout << "MyString(zoo) == MyString(hello) ==> " << (MyString("zoo") == MyString("hello")) << endl;	//0	  
        cout << "MyStrNoMove(zoo) < MyStrNoMove(hello) ==> " << (MyStrNoMove("zoo") < MyStrNoMove("hello")) << endl;	 //0
        cout << "MyStrNoMove(zoo) == MyStrNoMove(hello) ==> " << (MyStrNoMove("zoo") == MyStrNoMove("hello")) << endl;	 //0
                                                                                                                         //以上建構了 6 個 MyString objects 和 4 個 MyStrNoMove objects，都是暫時生命.    
    }
}
//--------------------------------------------------
#include <typeinfo>  //typeid()
template<typename T>
void output_static_data(const T& myStr)
{
    cout << typeid(myStr).name() << " -- " << endl;
    cout << " CCtor=" << T::CCtor
        << " MCtor=" << T::MCtor
        << " CAsgn=" << T::CAsgn
        << " MAsgn=" << T::MAsgn
        << " Dtor=" << T::Dtor
        << " Ctor=" << T::Ctor
        << " DCtor=" << T::DCtor
        << endl;
}

#include <ctime>  //clock_t, clock()
template<typename M, typename NM>
void test_moveable(M c1, NM c2, long& value)
{
    char buf[10];

    //測試 move 
    cout << "\n\ntest, with moveable elements" << endl;
    typedef typename iterator_traits<typename M::iterator>::value_type  V1type;
    clock_t timeStart = clock();
    for (long i = 0; i < value; ++i)
    {
        snprintf(buf, 10, "%d", rand());
        auto ite = c1.end();
        c1.insert(ite, V1type(buf));
    }
    cout << "construction, milli-seconds : " << (clock() - timeStart) << endl;
    cout << "size()= " << c1.size() << endl;
    output_static_data(*(c1.begin()));

    timeStart = clock();
    M c11(c1);
    cout << "copy, milli-seconds : " << (clock() - timeStart) << endl;

    timeStart = clock();
    M c12(std::move(c1));
    cout << "move copy, milli-seconds : " << (clock() - timeStart) << endl;

    timeStart = clock();
    c11.swap(c12);
    cout << "swap, milli-seconds : " << (clock() - timeStart) << endl;



    //測試 non-moveable 	
    cout << "\n\ntest, with non-moveable elements" << endl;
    typedef typename iterator_traits<typename NM::iterator>::value_type  V2type;
    timeStart = clock();
    for (long i = 0; i < value; ++i)
    {
        snprintf(buf, 10, "%d", rand());
        auto ite = c2.end();
        c2.insert(ite, V2type(buf));
    }

    cout << "construction, milli-seconds : " << (clock() - timeStart) << endl;
    cout << "size()= " << c2.size() << endl;
    output_static_data(*(c2.begin()));

    timeStart = clock();
    NM c21(c2);
    cout << "copy, milli-seconds : " << (clock() - timeStart) << endl;

    timeStart = clock();
    NM c22(std::move(c2));
    cout << "move copy, milli-seconds : " << (clock() - timeStart) << endl;

    timeStart = clock();
    c21.swap(c22);
    cout << "swap, milli-seconds : " << (clock() - timeStart) << endl;
}
//-----------------
long get_a_target_long()
{
    long target = 0;

    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    return target;
}

string get_a_target_string()
{
    long target = 0;
    char buf[10];

    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    snprintf(buf, 10, "%d", target);
    return string(buf);
}

int compareLongs(const void* a, const void* b)
{
    return (*(long*)a - *(long*)b);
}

int compareStrings(const void* a, const void* b)
{
    if (*(string*)a > *(string*)b)
        return 1;
    else if (*(string*)a < *(string*)b)
        return -1;
    else
        return 0;
}

#include <array>
#include <iostream>
#include <ctime> 
#include <cstdlib> //qsort, bsearch, NULL

namespace jj01
{
    void test_array()
    {
        cout << "\ntest_array().......... \n";

        array<long, ASIZE> c;

        clock_t timeStart = clock();
        for (long i = 0; i < ASIZE; ++i) {
            c[i] = rand();
        }
        cout << "milli-seconds : " << (clock() - timeStart) << endl;	//
        cout << "array.size()= " << c.size() << endl;
        cout << "array.front()= " << c.front() << endl;
        cout << "array.back()= " << c.back() << endl;
        cout << "array.data()= " << c.data() << endl;

        long target = get_a_target_long();

        timeStart = clock();
        ::qsort(c.data(), ASIZE, sizeof(long), compareLongs);
        long* pItem = (long*)::bsearch(&target, (c.data()), ASIZE, sizeof(long), compareLongs);
        cout << "qsort()+bsearch(), milli-seconds : " << (clock() - timeStart) << endl;	//    
        if (pItem != NULL)
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;
    }
}
//---------------------------------------------------
#include <vector>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
#include <algorithm> 	//sort()
namespace jj02
{
    void test_vector(long& value)
    {
        cout << "\ntest_vector().......... \n";

        vector<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try {
                snprintf(buf, 10, "%d", rand());
                c.push_back(string(buf));
            }
            catch (exception& p) {
                cout << "i=" << i << " " << p.what() << endl;
                //曾經最高 i=58389486 then std::bad_alloc
                abort();
            }
        }
        cout << "milli-seconds : " << (clock() - timeStart) << endl;
        cout << "vector.max_size()= " << c.max_size() << endl;	//1073747823
        cout << "vector.size()= " << c.size() << endl;
        cout << "vector.front()= " << c.front() << endl;
        cout << "vector.back()= " << c.back() << endl;
        cout << "vector.data()= " << c.data() << endl;
        cout << "vector.capacity()= " << c.capacity() << endl << endl;


        string target = get_a_target_string();
        {
            timeStart = clock();
            auto pItem = find(c.begin(), c.end(), target);
            cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

            if (pItem != c.end())
                cout << "found, " << *pItem << endl << endl;
            else
                cout << "not found! " << endl << endl;
        }

        {
            timeStart = clock();
            sort(c.begin(), c.end());
            cout << "sort(), milli-seconds : " << (clock() - timeStart) << endl;

            timeStart = clock();
            string* pItem = (string*)::bsearch(&target, (c.data()),
                c.size(), sizeof(string), compareStrings);
            cout << "bsearch(), milli-seconds : " << (clock() - timeStart) << endl;

            if (pItem != NULL)
                cout << "found, " << *pItem << endl << endl;
            else
                cout << "not found! " << endl << endl;
        }

        c.clear();
        test_moveable(vector<MyString>(), vector<MyStrNoMove>(), value);
    }
}

//---------------------------------------------------
#include <list>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <algorithm> //find()
#include <iostream>
#include <ctime> 
namespace jj03
{
    void test_list(long& value)
    {
        cout << "\ntest_list().......... \n";

        list<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try {
                snprintf(buf, 10, "%d", rand());
                c.push_back(string(buf));
            }
            catch (exception& p) {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds : " << (clock() - timeStart) << endl;
        cout << "list.size()= " << c.size() << endl;
        cout << "list.max_size()= " << c.max_size() << endl;    //357913941
        cout << "list.front()= " << c.front() << endl;
        cout << "list.back()= " << c.back() << endl;

        string target = get_a_target_string();
        timeStart = clock();
        auto pItem = find(c.begin(), c.end(), target);
        cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;

        timeStart = clock();
        c.sort();
        cout << "c.sort(), milli-seconds : " << (clock() - timeStart) << endl;

        c.clear();
        test_moveable(list<MyString>(), list<MyStrNoMove>(), value);
    }
}
//---------------------------------------------------
#include <forward_list>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj04
{
    void test_forward_list(long& value)
    {
        cout << "\ntest_forward_list().......... \n";

        forward_list<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try {
                snprintf(buf, 10, "%d", rand());
                c.push_front(string(buf));
            }
            catch (exception& p) {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds : " << (clock() - timeStart) << endl;
        cout << "forward_list.max_size()= " << c.max_size() << endl;  //536870911
        cout << "forward_list.front()= " << c.front() << endl;


        string target = get_a_target_string();
        timeStart = clock();
        auto pItem = find(c.begin(), c.end(), target);
        cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;

        timeStart = clock();
        c.sort();
        cout << "c.sort(), milli-seconds : " << (clock() - timeStart) << endl;

        c.clear();
    }
}
//---------------------------------------------------
#include <deque>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj05
{
    void test_deque(long& value)
    {
        cout << "\ntest_deque().......... \n";

        deque<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try {
                snprintf(buf, 10, "%d", rand());
                c.push_back(string(buf));
            }
            catch (exception& p) {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds : " << (clock() - timeStart) << endl;
        cout << "deque.size()= " << c.size() << endl;
        cout << "deque.front()= " << c.front() << endl;
        cout << "deque.back()= " << c.back() << endl;
        cout << "deque.max_size()= " << c.max_size() << endl;	//1073741821	

        string target = get_a_target_string();
        timeStart = clock();
        auto pItem = find(c.begin(), c.end(), target);
        cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;

        if (pItem != c.end())
            cout << "found, " << *pItem << endl;
        else
            cout << "not found! " << endl;

        timeStart = clock();
        sort(c.begin(), c.end());
        cout << "sort(), milli-seconds : " << (clock() - timeStart) << endl;

        c.clear();
        test_moveable(deque<MyString>(), deque<MyStrNoMove>(), value);
    }
}
//---------------------------------------------------
#include <set>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj06
{
    void test_multiset(long& value)
    {
        cout << "\ntest_multiset().......... \n";

        multiset<string> c;
        char buf[10];
        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try {
                snprintf(buf, 10, "%d", rand());
                c.insert(string(buf));
            }
            catch (exception& p) {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds : " << (clock() - timeStart) << endl;
        cout << "multiset.size()= " << c.size() << endl;
        cout << "multiset.max_size()= " << c.max_size() << endl;	//214748364

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto pItem = find(c.begin(), c.end(), target);	//比 c.find(...) 慢很多	
            cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;
        }

        {
            timeStart = clock();
            auto pItem = c.find(target);		//比 std::find(...) 快很多							
            cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;
        }

        c.clear();
        test_moveable(multiset<MyString>(), multiset<MyStrNoMove>(), value);
    }
}
//---------------------------------------------------
#include <map>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj07
{
    void test_multimap(long& value)
    {
        cout << "\ntest_multimap().......... \n";

        multimap<long, string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try {
                snprintf(buf, 10, "%d", rand());
                //multimap 不可使用 [] 做 insertion 
                c.insert(pair<long, string>(i, buf));
            }
            catch (exception& p) {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds : " << (clock() - timeStart) << endl;
        cout << "multimap.size()= " << c.size() << endl;
        cout << "multimap.max_size()= " << c.max_size() << endl;	//178956970	

        long target = get_a_target_long();
        timeStart = clock();
        auto pItem = c.find(target);
        cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
        if (pItem != c.end())
            cout << "found, value=" << (*pItem).second << endl;
        else
            cout << "not found! " << endl;

        c.clear();
    }
}
//---------------------------------------------------
#include <unordered_set>
#include <stdexcept>
#include <string>
#include <cstdlib> //abort()
#include <cstdio>  //snprintf()
#include <iostream>
#include <ctime> 
namespace jj08
{
    void test_unordered_multiset(long& value)
    {
        cout << "\ntest_unordered_multiset().......... \n";

        unordered_multiset<string> c;
        char buf[10];

        clock_t timeStart = clock();
        for (long i = 0; i < value; ++i)
        {
            try {
                snprintf(buf, 10, "%d", rand());
                c.insert(string(buf));
            }
            catch (exception& p) {
                cout << "i=" << i << " " << p.what() << endl;
                abort();
            }
        }
        cout << "milli-seconds : " << (clock() - timeStart) << endl;
        cout << "unordered_multiset.size()= " << c.size() << endl;
        cout << "unordered_multiset.max_size()= " << c.max_size() << endl;	//357913941
        cout << "unordered_multiset.bucket_count()= " << c.bucket_count() << endl;
        cout << "unordered_multiset.load_factor()= " << c.load_factor() << endl;
        cout << "unordered_multiset.max_load_factor()= " << c.max_load_factor() << endl;
        cout << "unordered_multiset.max_bucket_count()= " << c.max_bucket_count() << endl;
        for (unsigned i = 0; i < 20; ++i) {
            cout << "bucket #" << i << " has " << c.bucket_size(i) << " elements.\n";
        }

        string target = get_a_target_string();
        {
            timeStart = clock();
            auto pItem = find(c.begin(), c.end(), target);	//比 c.find(...) 慢很多	
            cout << "std::find(), milli-seconds : " << (clock() - timeStart) << endl;
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;
        }

        {
            timeStart = clock();
            auto pItem = c.find(target);		//比 std::find(...) 快很多							
            cout << "c.find(), milli-seconds : " << (clock() - timeStart) << endl;
            if (pItem != c.end())
                cout << "found, " << *pItem << endl;
            else
                cout << "not found! " << endl;
        }

        c.clear();
        test_moveable(unordered_multiset<MyString>(), unordered_multiset<MyStrNoMove>(), value);
    }
}
int main()
{
    long value = 500000;
    jj02::test_vector(value);
    return 0;
}