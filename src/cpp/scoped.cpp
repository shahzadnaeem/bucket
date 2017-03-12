#include <boost/scoped_ptr.hpp>
#include <iostream>
#include <string>

#include <memory>

using namespace std;

struct Shoe { static int i; ~Shoe() { std::cout << "Buckle my shoe: " << i++ << "\n"; } };

int Shoe::i = 0;

class MyClass {
  boost::scoped_ptr<int> ptr;
public:
  MyClass() : ptr(new int) { *ptr = 0; }
  ~MyClass() {}
  int add_one() { return ++*ptr; }
};

class Data {
public:
  int    tI;
  string tS;

  Data( int i, const string& s ) : tI( i ), tS( s ) {}
};

int main()
{
  boost::scoped_ptr<Shoe> x(new Shoe);

  MyClass my_instance;
  std::cout << my_instance.add_one() << '\n';
  std::cout << my_instance.add_one() << '\n';

  boost::scoped_ptr<Data> d( new Data( 2, "yo" ) );

  cout << "d->i = " << d->tI << ", d->s = " << d->tS << endl;

  // ===========================================================================

  typedef std::pair<int*,std::ptrdiff_t> mypair;

  std::auto_ptr<mypair> p (new mypair);

  *p = std::get_temporary_buffer<int>(5);

  if (p->second >= 5) {
    for (int i=0; i<5; i++)
      p->first[i]=i*5;

    for (int i=0; i<5; i++)
      std::cout << p->first[i] << " ";

    std::cout << '\n';
  }

  std::return_temporary_buffer (p->first);

  // ===========================================================================

  std::auto_ptr<Shoe> shoe1( new Shoe );
  std::auto_ptr<Shoe> shoe2( new Shoe );
  shoe2 = shoe1;

}
