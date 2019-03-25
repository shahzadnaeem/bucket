// ==============================================================================

#pragma once

// ==============================================================================

typedef vector<string> Args;
typedef Args::iterator ArgsIter;

// ==============================================================================

class BoardRunner
{
public:
  BoardRunner( int argc, char *argv[] );
  ~BoardRunner();

  int run();

private:
    Args tArgs;
};

// ==============================================================================
