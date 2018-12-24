// ==============================================================================

#include <vector>

#include "sudoku.h"

#include "boardrunner.h"

// ==============================================================================

BoardRunner::BoardRunner( int argc, char *argv[]) : tArgs( argv + 1, argv + argc )
{
}

// ==============================================================================

BoardRunner::~BoardRunner() {}

// ==============================================================================

int BoardRunner::run()
{
    Args::iterator it;

    for ( it = tArgs.begin(); it < tArgs.end(); it ++ )
    {
        cout << *it << endl;
    }

    return 0;
}

