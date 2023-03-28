#include <iostream>

struct A;
template <typename T> struct B;
template <typename T> struct X {
    typedef X<T> TA; // 编译器当然知道 X<T> 是一个类型。
    typedef X    TB; // X 等价于 X<T> 的缩写
    typedef T    TC; // T 不是一个类型还玩毛
    
    // ！！！注意我要变形了！！！
    class Y {
        typedef X<T>     TD;          // X 的内部，既然外部高枕无忧，内部更不用说了
        typedef X<T>::Y  TE;          // 嗯，这里也没问题，编译器知道Y就是当前的类型，
                                      // 这里在VS2015上会有错，需要添加 typename，
                                      // Clang 上顺利通过。
        typedef typename X<T*>::Y TF; // 这个居然要加 typename！
                                      // 因为，X<T*>和X<T>不一样哦，
                                      // 它可能会在实例化的时候被别的偏特化给抢过去实现了。
    };
    
    typedef A TG;                   // 嗯，没问题，A在外面声明啦
    typedef B<T> TH;                // B<T>也是一个类型
    typedef typename B<T>::type TI; // 嗯，因为不知道B<T>::type的信息，
                                    // 所以需要typename
    //typedef B<int>::type TJ;        // B<int> 不依赖模板参数，
                                    // 所以编译器直接就实例化（instantiate）了
                                    // 但是这个时候，B并没有被实现，所以就出错了
};

int main()
{
    return 0;
}