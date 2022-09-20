#include <iostream>

template <bool V>
struct answer
{
  answer(int) {}
  bool operator()() { return V; }
};

template <bool no, bool yes, int f, int p>
struct IsPrimeHelper
    : IsPrimeHelper<p % f == 0, f * f >= p, f + 2, p>
{
};

template <bool yes, int f, int p>
struct IsPrimeHelper<true, yes, f, p>
{
  using type = answer<false>;
};
template <int f, int p>
struct IsPrimeHelper<false, true, f, p>
{
  using type = answer<true>;
};

template <int I>
using IsPrime = typename IsPrimeHelper<!(I & 1), false, 3, I>::type;
template <int I>
struct X
{
  static const int i = I;
  int a[i];
};

template <typename A>
struct foo;

template <>
struct foo<answer<true>>
{
  template <int I>
  using typen = X<I>;
};

template <>
struct foo<answer<false>>
{
  static const int typen = 0;
};

int main()
{
  const int num = 977;

  // Here typen => using foo<answer<true>>::typen<1> = X<1>
  auto r = foo<IsPrime<num>>::typen<1>(); // Compiles because 977 is prime
  std::cout << num << " is prime" << std::endl;

  const int num2 = 993;

  // Here typen => template<> static const int foo<answer<false>>::typen = 0
  auto r2 = foo<IsPrime<num2>>::typen<1>(); // Does not compile - change num2 to a prime
  std::cout << num2 << " is prime" << std::endl;

  return 0;
}
