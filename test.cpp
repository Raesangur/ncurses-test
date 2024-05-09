#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>


class B;

template<typename T>
class C;

class A {

public: /* ... */

    template <typename T>
    typename C<T>::type add(const std::string& x) 
    {
        return C<T>::get(this, x);
    }

    void display()
    {
        std::cout << "A" << std::endl;
    }

    std::unique_ptr<B> b = nullptr;
}; 

class B
{
public:
    B(A* a) : a{a} {}

    void display()
    {
        std::cout << "B" << std::endl;
    }

    std::unique_ptr<A> a = nullptr;
};


template<typename T>
class C
{
public:
    typedef A& type;
    static type get(A* a, const std::string& x)
    {
        std::cout << "Getting A with " << x << std::endl;
        return *a;
    }
};

template<>
class C<int>
{
public:
    typedef B& type;
    static type get(A* a, const std::string x)
    {
        std::cout << "Getting B with " << x << std::endl;
        a->b = std::make_unique<B>(a);
        return *(a->b);
    }
};


int main()
{
    A a;

    auto x = a.add<void>(std::string{"Main menu"});
    /*
        .add<void>({"Option 1"})
        .add<int>({"Submenu 1"})
        .add(2);
        */
}