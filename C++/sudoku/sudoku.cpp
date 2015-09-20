// ==============================================================================

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

#include "sudoku.h"
#include "colour.h"

// ==============================================================================

using namespace std;
using namespace boost;

// ==============================================================================

Board::Board() : tPlaced( 0 ), tAttempts( 0 ), tSolutions( 0 ),
                 tValid( true ), tSolved( false ), tSolution()
{
  init();
}

// ==============================================================================

Board::Board( const string& stringIn ) : tPlaced(0), tAttempts( 0 ), tSolutions( 0 ),
                                         tValid( false ), tSolved( false ), tSolution()
{
  init();

  typedef char_separator<char> Separator;
  typedef tokenizer<Separator> Tokenizer;
  typedef Tokenizer::iterator  Iter;

  Separator sep( ",", "", boost::keep_empty_tokens );
  Tokenizer tokens( stringIn, sep );

  int items = distance( tokens.begin(), tokens.end() );

  if ( items <= cBoardDim )
  {
    int badItems = 0;
    int i = 0;

    for( Iter it = tokens.begin(); it != tokens.end(); it ++ )
    {
      if ( i == cBoardDim )
      {
        badItems ++;
        break;
      }

      try
      {
        int val = 0;

        if ( (*it).size() > 0 )
        {
          val = lexical_cast<int>( *it );
        }

        if ( ( val >= 0 ) && ( val <= cBoardSize ) )
        {
          tBoard[ i ] = val;
          tPlaced ++;
        }
        else
        {
          badItems ++;
        }
      }
      catch( boost::bad_lexical_cast & )
      {
        Separator sep( ":." );
        Tokenizer tokens( (*it), sep );

        int items = distance( tokens.begin(), tokens.end() );

        if ( items == 3 )
        {
          try
          {
            vector<string> tuple( tokens.begin(), tokens.end() );

            // Have a row:col:val
            int row = lexical_cast<int>( tuple[ 0 ] );
            int col = lexical_cast<int>( tuple[ 1 ] );
            int val = lexical_cast<int>( tuple[ 2 ] );

            if ( ( row * cBoardSize + col ) < cBoardDim )
            {
              i = row * cBoardSize + col;

              if ( ( val >= 0 ) && ( val <= cBoardSize ) )
              {
                tBoard[ i ] = val;
                tPlaced ++;
              }
              else
              {
                badItems ++;
              }
            }
            else
            {
              badItems ++;
            }
          }
          catch( boost::bad_lexical_cast & )
          {
            badItems ++;
          }
        }
        else
        {
          badItems ++;
        }
      }
      

      i ++;
    }

    tValid = ( badItems == 0 );

    for ( int i = 0; i < cBoardDim; i ++ )
    {
      tOrigBoard[ i ] = tBoard[ i ];
    }
  }
  else
  {
    cout << "ERROR #items = " << items << " expected <= " << cBoardDim << endl;
  }
}

// ==============================================================================

void Board::init()
{
  for ( int location = 0; location < cBoardDim; location ++ )
  {
    tBoard[ location ]     = cEmpty;
    tOrigBoard[ location ] = cEmpty;

    tNumCandidates[ location ] = cBoardSize;

    for( int value = 1; value <= cBoardSize; value ++ )
    {
      tAllowedValues[ location ][ value ] = true;
    }
  }
}

// ==============================================================================

Board::~Board()
{
}

// ==============================================================================

// placementCheck == true  => allow multiple 0 values to exist when checking
//                == false => this is a check for a valid set of positions

bool Board::checkPositions( Board::Positions positions, bool placementCheck )
{
  bool retVal = true;

  Checks checks;

  checks[ 0 ] = placementCheck;

  for ( int i = 1; i <= cBoardSize; i ++ )
  {
    checks[ i ] = true;
  }

  for ( int i = 0; i < cBoardSize; i ++ )
  {
    if ( checks[ tBoard[ positions[ i ] ] ] )
    {
      if ( ! placementCheck || ( tBoard[ positions[ i ] ] ) )
      { 
        checks[ tBoard[ positions[ i ] ] ] = false;
      }
    }
    else
    {
      retVal = false;
      break;
    }
  }

  return retVal;
}

// ==============================================================================

void Board::getRowPositions( int row, Positions& positions )
{
  int val = row * cBoardSize;

  for ( int i = 0; i < cBoardSize; i ++ )
  {
    positions[ i ] = val ++;
  }
}

bool Board::checkRow( int row, bool placementCheck )
{
  bool retVal = true;

  Positions positions;

  getRowPositions( row, positions );

  retVal = checkPositions( positions, placementCheck );

  return retVal;
}

// ==============================================================================

void Board::getColPositions( int col, Positions& positions )
{
  int val = col;

  for ( int i = 0; i < cBoardSize; i ++ )
  {
    positions[ i ] = val;

    val += cBoardSize;
  }
}

bool Board::checkCol( int col, bool placementCheck )
{
  bool retVal = true;

  Positions positions;

  getColPositions( col, positions );

  retVal = checkPositions( positions, placementCheck );

  return retVal;
}

// ==============================================================================

void Board::getBlockPositions( int block, Positions& positions )
{
  int row = ( block / cBlockSize ) * cBlockSize;
  int col = ( block % cBlockSize ) * cBlockSize;
  int i   = 0;

  for ( int r = 0; r < cBlockSize; r ++ )
  {
    for ( int c = 0; c < cBlockSize; c ++ )
    {
      positions[ i ++ ] = ( row + r ) * cBoardSize + col + c;
    }
  }
}

// ==============================================================================

bool Board::checkBlock( int block, bool placementCheck )
{
  bool retVal = true;

  Positions positions;

  getBlockPositions( block, positions );

  retVal = checkPositions( positions, placementCheck );

  return retVal;
}

// ==============================================================================

int Board::calculateAllowedValues( int location, Checks& allowedValues )
{
  int numCandidates = 0;
  int candidate     = 0;

  if ( tBoard[ location ] == cEmpty )
  {
    for ( int val = 1; val <= cBoardSize; val ++ )
    {
      allowedValues[ val ] = true;
    }

    int row   = location / cBoardSize;
    int col   = location % cBoardSize;
    int block = ( location / cBlockSize ) % cBlockSize;

    block += (( ( location / cBoardSize ) / cBlockSize ) % cBlockSize ) * cBlockSize;

    Positions positions;

    getRowPositions( row, positions );

    for ( int i = 0; i < cBoardSize; i ++ )
    {
      if ( tBoard[ positions[ i ] ] )
      {
        allowedValues[ tBoard[ positions[ i ] ] ] = false;
      }
    }

    getColPositions( col, positions );

    for ( int i = 0; i < cBoardSize; i ++ )
    {
      if ( tBoard[ positions[ i ] ] )
      {
        allowedValues[ tBoard[ positions[ i ] ] ] = false;
      }
    }

    getBlockPositions( block, positions );

    for ( int i = 0; i < cBoardSize; i ++ )
    {
      if ( tBoard[ positions[ i ] ] )
      {
        allowedValues[ tBoard[ positions[ i ] ] ] = false;
      }
    }

    for ( int val = 1; val <= cBoardSize; val ++ )
    {
      if ( allowedValues[ val ] )
      {
        numCandidates ++;
        candidate = val;
      }
    }

    if ( 0 ) // numCandidates == 1 )
    {
      int row = location / cBoardSize;
      int col = location % cBoardSize;

      cout << "# Optimisation possible: ( " << row << ", " << col
      << " ): " << candidate << " is only candidate" << endl;
    }
  }

  return numCandidates;
}

// ==============================================================================

//
// By looking at what is on the board initially, a set of candidate values
// for each location can be determined
//

void Board::calculateAllAllowedValues()
{
  bool done = true;

  do
  {
    for( int location = 0; location < cBoardDim; location ++ )
    {
      int numCandidates = calculateAllowedValues( location, tAllowedValues[ location ] );

      tNumCandidates[ location ] = numCandidates;

      // TODO: Optimise locations with only 1 candidate
    }
  }
  while ( ! done );
}

// ==============================================================================

bool Board::isSolved()
{
  bool retVal = true;

  for ( int i = 0; i < cBoardSize; i ++ )
  {
    if ( retVal )
      retVal = checkRow( i );

    if ( retVal )
      retVal = checkCol( i );

    if ( retVal )
      retVal = checkBlock( i );

    if ( ! retVal )
      break;
  }

  return retVal;
}

// ==============================================================================

bool Board::doSolve( int location )
{
  bool retVal = false;

  if ( location != cBoardDim )
  {
    if ( tBoard[ location ] == cEmpty )
    {
      Checks allowedValues;

      calculateAllowedValues( location, allowedValues );

      for ( int val = 1; val <= cBoardSize; val ++ )
      {
        if ( allowedValues[ val ] )
        {
          tAttempts ++;

          if ( canPlace( location, val ) )
          {
            if ( retVal = doSolve( location + 1 ) )
            {
              break;  // REMOVE THIS IF ALL SOLUTIONS ARE NEEDED
                      // WILL DISPLAY FINAL SOLUTION AND TOTAL COUNT

              tBoard[ location ] = cEmpty;
            }
          }
        }
      }

      if ( ! retVal )
      {
        tBoard[ location ] = cEmpty;  // Allow back tracking to start afresh
      }
    }
    else
    {
      retVal = doSolve( location + 1 );
    }
  }
  else
  {
    if ( retVal = isSolved() )
    {
      // Take a snapshot of this solution - there may be more ...

      ostringstream os;

      tSolved = true;

      os << toDisplay();

      tSolution = os.str();

      tSolutions ++;
    }
  }

  return retVal;
}

// ==============================================================================

bool Board::solve()
{
  (void) doSolve( 0 );

  return tSolved;
}

// ==============================================================================

bool Board::canPlace( int location, int value )
{
  bool retVal = false;

  if ( ( location >= 0 ) && ( location < cBoardDim ) )
  {
    retVal = true;

    int row   = location / cBoardSize;
    int col   = location % cBoardSize;
    int block = ( location / cBlockSize ) % cBlockSize;

    block += (( ( location / cBoardSize ) / cBlockSize ) % cBlockSize ) * cBlockSize;

    int savedValue = tBoard[ location ];

    tBoard[ location ] = value;

    retVal = checkRow( row, true );

    if ( retVal )
    {
      retVal = checkCol( col, true );
    }

    if ( retVal )
    {
      retVal = checkBlock( block, true );
    }

    if ( ! retVal )
    {
      tBoard[ location ] = savedValue;
    }
  }

  return retVal;
}

// ==============================================================================

string Board::toString() const
{
  ostringstream os;

  for ( int i = 0; i < cBoardDim; i ++ )
  {
    if ( i > 0 )
    {
      os << ",";
    }

    os << tBoard[ i ];
  }
  
  return os.str();
}

// ==============================================================================

ostringstream& Board::displayLine( ostringstream& os ) const
{
  for ( int i = 0; i < cBoardSize; i ++ )
  {
    os << "+---";
  }
  os << "+";
}

// ==============================================================================

string Board::toDisplay() const
{
  ostringstream os;

  displayLine( os );

  for ( int i = 0; i < cBoardDim; i ++ )
  {
    if ( i % cBoardSize == 0 )
    {
      os << endl << "|";
    }

    if ( tBoard[ i ] )
    {
      os << " ";

      if ( tOrigBoard[ i ] )
      {
        os << Colour( Colour::RED );
      }
      else
      {
        os << Colour( Colour::GREEN );
      }

      os << tBoard[ i ] << Colour() << " |";
    }
    else
    {
      os << " . |";
    }

    if ( i % cBoardSize == ( cBoardSize - 1 ) )
    {
      os << endl;

      if ( i != ( cBoardDim -1 ) )
      {
        displayLine( os );
      }
    }
  }

  displayLine( os );

  return os.str();
}

// ==============================================================================

ostream& operator<<( ostream& os, const Board& rhs )
{
  os << rhs.toString();

  return os;
}

// ==============================================================================
