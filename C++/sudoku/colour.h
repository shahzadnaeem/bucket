// ==============================================================================

#pragma once

// ==============================================================================

#include <iostream>

// ==============================================================================

using namespace std;

// ==============================================================================

// ANSI terminal coloured text

class Colour
{
public:
  enum Colours { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, NONE, BRIGHT, NORMAL };

  Colour( Colours colour = NONE ) : tColour( colour ) {};

  ostream& operator()( ostream& os ) const;

  friend ostream& operator<<( ostream& os, Colour c )
  {
    return c( os );
  }

private:
  Colours tColour;
};

// ==============================================================================
