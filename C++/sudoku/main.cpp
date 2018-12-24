// ==============================================================================

#include <iostream>
#include <vector>

#include <boost/timer.hpp>

#include <stdlib.h>

#include "sudoku.h"
#include "boardrunner.h"

using namespace std;
using namespace boost;

// ==============================================================================

typedef vector<string> Args;
typedef Args::iterator ArgsIter;

// ==============================================================================

int main( int argc, char *argv[] )
{
  int exitVal = EXIT_SUCCESS;

  BoardRunner boardRunner( argc, argv );

  boardRunner.run();

  exit( 0 );

  if ( argc > 1 )
  {
    Args args( argv + 1, argv + argc );

    cout << endl << "Trying your board" << ( ( argc > 2 ) ? "s" : "" ) << " ..." << endl;

    ArgsIter it;

    for ( it = args.begin(); it < args.end(); it ++ )
    {
      try
      {
        cout << "# Board: " << *it << endl;

        Board *pBoard = new Board( *it );

        if ( pBoard->isValid() )
        {
          cout << pBoard->toDisplay() << endl;

          bool solved = pBoard->isSolved();

          cout << ( solved ? "SOLVED" : "NOT SOLVED" ) << endl << endl;

          if ( ! solved )
          {
            timer t;

            if ( pBoard->solve() )
            {
              cout << pBoard->getSolution() << endl;
              cout << "SOLVED" << endl;
            }
            else
            {
              cout << pBoard->toDisplay() << endl;
              cout << "Can't SOLVE!" << endl;
              exitVal = EXIT_FAILURE;
            }

            cout << pBoard->numAttempts() << " attempts, ";
            cout << pBoard->numSolutions() << " solution"
                 << (( pBoard->numSolutions() > 1 ) ? "s" : "" ) << endl;

            cout << t.elapsed() << "s" << endl;
          }
        }
        else
        {
          cout << pBoard->toDisplay() << endl;

          cout << "Bad board!" << endl;
          exitVal = EXIT_FAILURE;
        }

        delete pBoard;
      }
      catch( ... )
      {
        cout << endl << *it << endl << "IS A VERY BAD BOARD!" << endl;

        exitVal = EXIT_FAILURE;
      }
    }
  }
  else
  {
    Board aBoard( "1,2,3,4,5,6,7,8,9,"
                  "4,5,6,7,8,9,1,2,3,"
                  "7,8,9,1,2,3,4,5,6,"
                  "2,3,4,0,0,0,8,9,1,"
                  "5,6,7,8,9,1,2,3,4,"
                  "8,9,1,2,3,4,5,6,7,"
                  "3,4,5,6,7,8,9,1,2,"
                  "6,7,8,9,1,2,3,4,5,"
                  "9,1,2,3,4,5,6,7,0"
                );

    cout << aBoard.toDisplay() << endl;

    bool solved = aBoard.isSolved();

    cout << ( solved ? "SOLVED" : "NOT SOLVED" ) << endl << endl;

    solved = aBoard.solve();

    cout << aBoard.toDisplay() << endl;

    cout << ( solved ? "SOLVED" : "NOT SOLVED" );

    solved = aBoard.isSolved();

    cout << " [double check: " << ( solved ? "SOLVED" : "NOT SOLVED" ) << "]" << endl;

    exitVal = solved ? EXIT_SUCCESS : EXIT_FAILURE;
  }

  return( exitVal );
}

// ==============================================================================
