
#include <vector>
#include <type_traits>
#include <string>
#include <iostream>

using namespace std;

//template<class C>
//using Value_Type = typename std::remove_reference<
//        decltype(*std::begin(std::declval<
//            typename std::add_lvalue_reference<C>::type>()))>::type;

// New type alias syntax - defines Value_type as ...
template <class T>
using Value_type = typename T::value_type;

template<typename C, typename V>

vector<Value_type<C>*> find_all( C& c, V v )
{
  vector<Value_type<C>*> res;

  for( auto& x : c )
  {
    if ( x == v )
      res.push_back( &x );
  }

  return res;
}

void argvToVec( int argc, char** argv, vector<string>& vec )
{
  vec.clear();

  for( int i = 1; i < argc; i ++ )
  {
    vec.push_back( string( argv[i] ) );
  }
}

template<typename C, typename V>
void showValInThing( C& c, V v )
{
  cout << "'" << v << "'s in " << c << endl;
  
  for( const auto p : find_all( c, v ) )
  {
    cout << *p << ',';
  } 
  cout << endl;
}

int main( int argc, char *argv[] )
{
  string m {"What is happening here?"};

  showValInThing( m, 'a' );

  vector<string> argvec;

  argvToVec( argc, argv, argvec );

  for( auto a : argvec )
  {
    showValInThing( a, 'a' );
  }
}

