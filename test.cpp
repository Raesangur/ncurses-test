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
    ~A()
    {
        b.release();
    }

    template <typename T>
    typename C<T>::type add(const std::string& x) 
    {
        return C<T>::get(this, x);
    }

    A& clean_child()
    {
        //b.reset();
        return *this;
    }
    
    std::unique_ptr<B> b = nullptr;
}; 

class B
{
public:
    B(A* a) : a{a} {}

    template <typename T>
    B& add(const std::string& x) 
    {
        std::cout << "Getting B with " << x << " - " << name << std::endl;
        return *this;
    }

    B& finish()
    {
        B* parent = parent_b;
        delete this;
        return *parent;
    }

    A& full_finish()
    {
        A* parent = a;
        a->b.reset();
        return *parent;
    }

    std::string name;
    A* a = nullptr;
    B* parent_b = nullptr;
    std::unique_ptr<B> b = nullptr;
};

template <>
B& B::add<int>(const std::string& x) 
{
    std::cout << "Going deeper in B with " << x << " - " << name << std::endl;
    b = std::make_unique<B>(a);
    b->name = x;
    b->parent_b = this;
    return *b;
}


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
        a->b->name = x;
        return *(a->b);
    }
};


int main()
{
    A a;

    auto& x = a.add<void>(std::string{"Main menu"})
        .add<void>({"Option 1"})
        .add<int>({"Submenu 1"})
            .add<void>({"Option 2"})
            .add<void>({"Option 3"})
                .add<int>({"Deeper submenu"})
                .add<void>({"Option 4"})
                .finish()
            .add<void>({"Option 5"})
        .full_finish().clean_child()
        .add<void>({"Option 6 motherfuckers"});

    std::cout << "Oh fuck" << std::endl;
}