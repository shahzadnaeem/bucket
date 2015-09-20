// ==============================================================================

#include "colour.h"

// ==============================================================================

ostream& Colour::operator()( ostream& os ) const
{
  switch( tColour )
  {
    case RED:
    {
      os << "\033[31m";
    }
    break;

    case GREEN:
    {
      os << "\033[32m";
    }
    break;

    case BLUE:
    {
      os << "\033[34m";
    }
    break;

    case YELLOW:
    {
      os << "\033[33m";
    }
    break;

    case BRIGHT:
    {
      os << "\033[1m";
    }
    break;

    case WHITE:
    case NORMAL:
    case NONE:
    default:
    {
      os << "\033[0m";
    }
  }

  return os;
}

// ==============================================================================
