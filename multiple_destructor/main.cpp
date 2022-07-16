#define cpp20 1

#include <utility>
#include <type_traits>
#include <string>

// Cosntructor is user defined
struct NotTrivial
{
  int foo;
  std::string bar2;

  NotTrivial()  {};
};

// compiler auto generaet copy constructor/assignment etc
struct Trivial
{
  int foo;

  Trivial() = default;
};

#ifndef cpp20
// for c++11, create multiple destructors way
template<typename Type>
struct Optional_nontrivial
{
    ~Optional_nontrivial()
    {
        static_cast<Type *>(this)->data.~Contained();
    }
};

struct Optional_trivial
{

};
#endif

// attempt to mimic std::optional
template<typename Contained>
#ifdef cpp20
// c++20 multiple destructor
struct Optional
{
    union {Contained data;};
    bool initialized = false;

    constexpr Optional &operator=(Contained &&data)
    {
        this->data = std::move(data);
        initialized = true;
        return *this;
    }

    // cpp20 can make constexpr destructor
    constexpr ~Optional() requires(!std::is_trivially_destructible_v<Contained>)
    {
        if(initialized)
        {
            data.~Contained();
        }
    }

    constexpr ~Optional() = default;
};
#else
// non c++20 way to handling trivial/nontrivial type 
struct Optional : std::conditional<std::is_trivially_destructible_v<Contained>,
                    Optional_trivial,
                    Optional_nontrivial<Optional<Contained>>>
{
    union {Contained data;};
    bool initialized = false;

    constexpr Optional &operator=(Contained &&data)
    {
        this->data = std::move(data);
        initialized = true;
        return *this;
    }
};
#endif

int main()
{
    Optional<int> obj;
    obj.data = 5;
    Optional<Trivial> obj_trivial;

    static_assert(std::is_trivially_destructible_v<Optional<int>>);
    static_assert(std::is_trivially_destructible_v<Optional<Trivial>>);
    static_assert(!std::is_trivially_destructible_v<Optional<std::string>>);
    static_assert(!std::is_trivially_destructible_v<Optional<NotTrivial>>);
}