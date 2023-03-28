#include <complex>
#include <type_traits>
//Concept “概念”：对模板参数约束的直接描述
template <typename ArgT>
void foo(
    ArgT&& a, 
    typename std::enable_if<
        std::is_same<std::decay_t<ArgT>, float>::value
    >::type* = nullptr
);
// Concept
template <typename ArgT>
  requires std::same_as<std::remove_cvref<ArgT>, float> 
void foo(ArgT&& a)  {
}

template <typename T> concept Incrementable = requires (T t) { ++t; };
template <Incrementable T>
void inc_counter(T& intTypeCounter) { 
    ++intTypeCounter;
}

int main()
{
	return 0;
}