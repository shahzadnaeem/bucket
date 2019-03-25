// ==============================================================================

#pragma once

// ==============================================================================

#include <iostream>
#include <sstream>
#include <string>

// ==============================================================================

using namespace std;

// ==============================================================================

class Board
{
public:
  Board();
  Board( const string& stringIn );
  
  Board( const Board& rhs );

  ~Board();

  bool isValid()       { return tValid; }
  int  numPlaced()     { return tPlaced; }
  int  numAttempts()   { return tAttempts; }
  int  numSolutions()  { return tSolutions; }
  string getSolution() { return tSolution; }

  bool isSolved();
  bool solve();

  string toString() const;
  string toDisplay() const;

  friend ostream& operator<<( ostream& os, const Board& rhs );

private:
  static const int cBlockSize = 3;
  static const int cBoardSize = cBlockSize * cBlockSize;
  static const int cBoardDim  = cBoardSize * cBoardSize;
  static const int cEmpty     = 0;

  typedef int  Positions[ cBoardSize ];
  typedef bool Checks[ cBoardSize + 1 ];

  int    tBoard[ cBoardDim ];
  int    tOrigBoard[ cBoardDim ];
  Checks tAllowedValues[ cBoardDim ];
  int    tNumCandidates[ cBoardDim ];

  int    tPlaced;
  int    tAttempts;
  int    tSolutions;
  bool   tValid;
  bool   tSolved;
  string tSolution;

private:
  void init();

  int  calculateAllowedValues( int location, Checks& allowedValues );
  void calculateAllAllowedValues();

  ostringstream& displayLine( ostringstream& os ) const;

  bool checkPositions( Positions positions, bool placementCheck = false );

  void getRowPositions( int row, Positions& positions );
  void getColPositions( int col, Positions& positions );
  void getBlockPositions( int block, Positions& positions );  

  bool checkRow( int row, bool placementCheck = false );
  bool checkCol( int col, bool placementCheck = false );
  bool checkBlock( int block, bool placementCheck = false );

  bool canPlace( int location, int value );
  bool doSolve( int location );
};

// ==============================================================================
