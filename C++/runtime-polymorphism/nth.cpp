#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <algorithm>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void show_nth( vector<int>& vi, int n )
{
    for( auto itr = vi.begin(); itr != vi.end(); itr ++ )
    {
        if ( itr == (vi.begin()+(n-1)) ) cout << '|';
        cout << *itr;
        if ( itr == (vi.begin()+(n-1)) ) cout << '|';
        cout << ' ';
    }
    cout << endl;
}

static int cmp_count  = 0;
static int swap_count = 0;

void reset_counts()
{
    cmp_count = 0;
    swap_count = 0;
}

template <typename Iter1, typename Iter2>
void my_swap( Iter1 a, Iter2 b )
{
    swap_count ++;
    swap( *a, *b );
}

void nth_sort( vector<int>& vi, int n )
{
    for ( auto otr = vi.begin(); otr != vi.begin()+n; otr ++ )
    {
        for ( auto itr = otr + 1; itr != vi.end(); itr ++ )
        {
            cmp_count ++;
            if ( *otr > *itr ) {
                my_swap( otr, itr );
                // auto tmp = *otr;
                // *otr = *itr;
                // *itr = tmp;
            }
        }
    }
}

void run_nth( int argc, char *argv[] )
{
    vector<int> vi { 10, 9, 1, 2, 3, 5, 7, 10, 8, 6};
    int n = 3;

    if ( argc == 2 )
    {
        n = atoi( argv[1] );
    }

    show_nth( vi, n );
    nth_sort( vi, n );
    show_nth( vi, n );

    cout << "Length: " << vi.size() << ", Swaps: " << swap_count << ", compares: " << cmp_count << endl;
}

void run_reverse( int argc, char *argv[] )
{
    vector<string> args( argv + 1, argv + argc );

    for( auto arg : args  )
    {
        cout << arg << " => ";

        auto b = arg.begin();
        auto e = arg.end();

        while ( ( b != e ) && (b != --e) )
        {
            my_swap(b, e);
            b++;
        }

        //reverse( arg.begin(), arg.end() );
        cout << arg << endl;
    }
}

int main( int argc, char *argv[])
{
  //run_reverse( argc, argv );

  run_nth( argc, argv );
}
