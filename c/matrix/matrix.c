// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// -----------------------------------------------------------------------------

#include <ncurses.h>

// -----------------------------------------------------------------------------

int SyncDelay = 9000;

// -----------------------------------------------------------------------------

unsigned char chA[] = { 0x00, 0x1c, 0x22, 0x42, 0x42, 0x7e, 0x42, 0x42 };
unsigned char chB[] = { 0x00, 0x78, 0x44, 0x44, 0x78, 0x44, 0x44, 0x7c };
unsigned char ch_SPC[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
unsigned char ch_ALL[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

unsigned char font[][8] = {
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // SPC
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, // ALL-ON
  {0x00,0x1c,0x22,0x42,0x42,0x7e,0x42,0x42}, // A
  {0x00,0x78,0x44,0x44,0x78,0x44,0x44,0x7c}, // B
  {0x00,0x3c,0x44,0x40,0x40,0x40,0x44,0x7c}, // C
  {0x00,0x7c,0x42,0x42,0x42,0x42,0x44,0x78}, // D
  {0x00,0x78,0x40,0x40,0x70,0x40,0x40,0x7c}, // E
  {0x00,0x7c,0x40,0x40,0x78,0x40,0x40,0x40}, // F
  {0x00,0x3c,0x40,0x40,0x5c,0x44,0x44,0x78}, // G
  {0x00,0x42,0x42,0x42,0x7e,0x42,0x42,0x42}, // H
  {0x00,0x7c,0x10,0x10,0x10,0x10,0x10,0x7e}, // I
  {0x00,0x7e,0x02,0x02,0x02,0x02,0x04,0x38}, // J
  {0x00,0x44,0x48,0x50,0x60,0x50,0x48,0x44}, // K
  {0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x7c}, // L
  {0x00,0x82,0xc6,0xaa,0x92,0x82,0x82,0x82}, // M
  {0x00,0x42,0x42,0x62,0x52,0x4a,0x46,0x42}, // N
  {0x00,0x3c,0x42,0x42,0x42,0x42,0x44,0x38}, // O
  {0x00,0x78,0x44,0x44,0x48,0x70,0x40,0x40}, // P
  {0x00,0x3c,0x42,0x42,0x52,0x4a,0x44,0x3a}, // Q
  {0x00,0x78,0x44,0x44,0x78,0x50,0x48,0x44}, // R
  {0x00,0x38,0x40,0x40,0x38,0x04,0x04,0x78}, // S
  {0x00,0x7e,0x90,0x10,0x10,0x10,0x10,0x10}, // T
  {0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x3e}, // U
  {0x00,0x42,0x42,0x42,0x42,0x44,0x28,0x10}, // V
  {0x80,0x82,0x82,0x92,0x92,0x92,0x94,0x78}, // W
  {0x00,0x42,0x42,0x24,0x18,0x24,0x42,0x42}, // X
  {0x00,0x44,0x44,0x28,0x10,0x10,0x10,0x10}, // Y
  {0x00,0x7c,0x04,0x08,0x7c,0x20,0x40,0xfe}, // Z
};

// -----------------------------------------------------------------------------

#define FONT(c) font[(c - 'A' + 2)]

// -----------------------------------------------------------------------------

typedef struct pos { int x; int y; } pos_t;

// -----------------------------------------------------------------------------

pos_t spiral( int size, pos_t in )
{
  pos_t out  = { size / 2, size / 2 - 1 };
  pos_t iter = { 0, 0 };

  int inc_y    = 1;
  int inc      = 1;
  int inc_l    = 1;
  int inc_curl = 1;

  while ( iter.x != in.x || iter.y != in.y ) {
    if ( inc_y ) {
      out.y += inc;
      inc_curl --;

      if ( inc_curl == 0 ) {
        inc_y    = 0;
        inc_curl = inc_l;
        inc      = - inc;
      }
    } else {
      out.x += inc;
      inc_curl --;

      if ( inc_curl == 0 ) {
        inc_y    = 1;
        inc_l ++;
        inc_curl = inc_l;
      }
    }

    iter.x ++;
    if ( iter.x == size ) {
      iter.x = 0;
      iter.y ++;
    }
  }

  return out;
}

pos_t rev_spiral( int size, pos_t in )
{
  pos_t out = spiral( size, in );

  int tmp = out.x;
  out.x = out.y;
  out.y = tmp;

  return out;
}

void showChar( int size, int y, int x, unsigned char *ch )
{
  for ( int i = 0; i < size; i ++ ) {
    for ( int j = 0; j < size; j ++ ) {

      unsigned char mask = 1 << ( size - 1 - j );

      unsigned char bit = ch[i] & mask;

      move( y * size + i, x * size + j );

      printw( bit ? "#" : "." );

      usleep( SyncDelay );
      refresh();
    }
  }
}

void showCharFast( int size, int y, int x, unsigned char *ch )
{
  for ( int i = 0; i < size; i ++ ) {
    for ( int j = 0; j < size; j ++ ) {

      unsigned char mask = 1 << ( size - 1 - j );

      unsigned char bit = ch[i] & mask;

      move( y * size + i, x * size + j );

      printw( bit ? "#" : "." );
    }
  }

  refresh();
}

void showScroll( int size, int y, int x, int pos, unsigned char *ch1, unsigned char *ch2 )
{
  unsigned char newChar[size];

  for ( int i = 0; i < size; i ++ ) {
    newChar[i] = ( ( ch1[i] << pos ) | ( ch2[i] >> ( size - pos ) ) & 0xFF );
 }

  showCharFast( size, y, x, newChar );
}

void scrollString( int size, int y, int x, int width, char* string )
{
  int len     = strlen( string );
  int pos     = 0;
  int lastPos = len - width;

  if ( lastPos < 0 ) {
    lastPos = pos;
  }

  int i = 0;
  do {
    for ( int p = 0; p < size; p ++ ) {
      for ( int j = 0; j < width; j ++ ) {
        showScroll( size, y, x + j, p, FONT(string[i+j]), FONT(string[i+j+1]) );
      }
      usleep( 50000 );
    }

    i ++;
  } while ( i < lastPos );
}

void showCharSpiral( int size, int y, int x, unsigned char *ch )
{
  for ( int i = 0; i < size; i ++ ) {
    for ( int j = 0; j < size; j ++ ) {

      pos_t in = { j, i };

      pos_t out = spiral( size, in );

      unsigned char mask = 1 << ( size - 1 - out.x );

      unsigned char bit = ch[ out.y ] & mask;

      move( y * size + out.y, x * size + out.x );

      printw( bit ? "#" : "." );

      usleep( SyncDelay );
      refresh();
    }
  }
}

void showCharWipe( int size, int y, int x, unsigned char *ch, int vert, int dir )
{
  int is, ii, js, ji;

  for ( int i = 0; i < size; i ++ ) {
    for ( int j = 0; j < size; j ++ ) {

      unsigned char mask;
      unsigned char bit;

      if ( vert ) {
        if ( dir ) {
          mask = 1 << ( size - 1 - i );
          bit = ch[ j ] & mask;
          move( y * size + j, x * size + i );
        } else {
          mask = 1 << ( i );
          bit = ch[ j ] & mask;
          move( y * size + j, x * size + size - 1 - i );
        }
      } else {
        if ( dir ) {
          mask = 1 << ( size - 1 - j );
          bit = ch[ i ] & mask;
          move( y * size + i, x * size + j );
        } else {
          mask = 1 << ( j );
          bit = ch[ size - 1 - i ] & mask;
          move( y * size + size - 1 - i, x * size + size - 1 - j );
        }
      }

      printw( bit ? "#" : "." );
    }

    usleep( SyncDelay / size );
    refresh();
  }
}

void showCharRand( int size, int y, int x, unsigned char *ch )
{
  int a = 0;

  for ( int c = 0; c < size * size; c ++ ) {

    int i = a / 8;
    int j = a % size;

    unsigned char mask = 1 << ( size - 1 - j );
    unsigned char bit = ch[i] & mask;

    move( y * size + i, x * size + j );

    printw( bit ? "#" : "." );

    usleep( SyncDelay );
    refresh();

    if ( c != 0 ) {
      do
      {
        int newbit = (((a >> 6) ^ (a >> 5)) & 1);
        a = ((a << 1) | newbit) & 0x7f;
      } while ( a >= size * size );
    } else {
      a = 61;
    }
  }
}

void testSpiral()
{
  int y, x;
  int size = 4;

  for ( int y = 0; y < size; y ++ )
    for ( int x = 0; x < size; x ++ ) {

      pos_t in      = { x, y };
      pos_t out     = spiral( size, in );
      pos_t rev_out = rev_spiral( size, in );

      printf( "in: (%d,%d) => (%d,%d), rev(%d,%d)\n", in.x, in.y, out.x, out.y, rev_out.x, rev_out.y );
    }

  exit(1);
}

// -----------------------------------------------------------------------------

void demo()
{
  int res = -1;
  int i   = 0;

  
  showCharRand( 8, 0, 1, FONT('J') );
  showCharRand( 8, 0, 1, FONT('E') );
  showCharRand( 8, 0, 1, FONT('N') );
  showCharRand( 8, 0, 1, FONT('N') );
  showCharRand( 8, 0, 1, FONT('Y') );

  scrollString( 8, 1, 2, 4, "????HELLO?JENNY?JENNY??????BYE!" );

  while ( res == -1 ) {

    for ( i = 0; i <= 8; i ++ ) {
      showScroll( 8, 0, 1, i, FONT('J'), font[1] );

      usleep( 200000 );
    }

    timeout( 1000 );
    res = getch();
  }

  showChar( 8, 1, 3, chA );
  showChar( 8, 1, 4, chB );

  showCharWipe( 8, 0, 3, FONT('J'), 0, 0 );
  showCharWipe( 8, 0, 4, FONT('E'), 0, 1 ); 
  showCharWipe( 8, 0, 5, FONT('N'), 1, 0 ); 
  showCharWipe( 8, 0, 6, FONT('N'), 1, 1 ); 
  showCharWipe( 8, 0, 7, FONT('Y'), 0, 0 ); 

  showCharWipe( 8, 1, 5, ch_SPC, 0, 0 );
  showCharWipe( 8, 1, 5, ch_ALL, 0, 1 );
  showCharWipe( 8, 1, 5, ch_SPC, 1, 0 );
  showCharWipe( 8, 1, 5, ch_ALL, 1, 1 );
  showCharWipe( 8, 1, 5, ch_SPC, 0, 0 );

  while ( res == -1 ) {

    showCharSpiral( 8, 1, 6, font[i] );

    showCharSpiral( 8, 1, 7, ch_ALL );
    showCharWipe( 8, 1, 7, font[i], i % 4 / 2, (i % 4) % 2 );

    i++;

    if ( i == ( sizeof( font ) / sizeof( *font ) ) ) {
      i = 0;
    }

    refresh();

    timeout( 1000 );
    res = getch();

    move( 20, 0 );
      printw( "i = %d, res = %5d, font = %d, %d",
              i,
              res,
              sizeof( font )/sizeof( *font ),
              sizeof( *font ) );

    refresh();
  }
}

// -----------------------------------------------------------------------------

unsigned char jennySymbols[][8] = {
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // SPC    - SPACE
  {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}, // ALL-ON - !
  {0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0xFF}, // ALT    - "
  {0x7E,0x42,0x42,0x42,0x42,0x42,0x42,0x7E}  // ALT    - #
};

unsigned char jennyFont[][8] = {
  {0x00,0x38,0x44,0x4c,0x54,0x64,0x44,0x38}, // 0
  {0x04,0x0c,0x14,0x24,0x04,0x04,0x04,0x04}, // 1
  {0x00,0x30,0x48,0x04,0x04,0x38,0x40,0x7c}, // 2
  {0x00,0x38,0x04,0x04,0x18,0x04,0x44,0x38}, // 3
  {0x00,0x04,0x0c,0x14,0x24,0x7e,0x04,0x04}, // 4
  {0x00,0x7c,0x40,0x40,0x78,0x04,0x04,0x38}, // 5
  {0x00,0x38,0x40,0x40,0x78,0x44,0x44,0x38}, // 6
  {0x00,0x7c,0x04,0x04,0x08,0x08,0x10,0x10}, // 7
  {0x00,0x3c,0x44,0x44,0x38,0x44,0x44,0x78}, // 8
  {0x00,0x38,0x44,0x44,0x3c,0x04,0x04,0x78}, // 9
  {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00}, // :
  {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x08}, // ;
  {0x00,0x10,0x20,0x40,0x80,0x40,0x20,0x10}, // <
  {0x00,0x00,0x7e,0x00,0x00,0xfc,0x00,0x00}, // =
  {0x00,0x08,0x04,0x02,0x01,0x02,0x04,0x08}, // >
  {0x00,0x38,0x44,0x04,0x08,0x10,0x00,0x10}, // ?
  {0x00,0x30,0x48,0xba,0xba,0x84,0x78,0x00}, // @
  {0x00,0x1c,0x22,0x42,0x42,0x7e,0x42,0x42}, // A
  {0x00,0x78,0x44,0x44,0x78,0x44,0x44,0x7c}, // B
  {0x00,0x3c,0x44,0x40,0x40,0x40,0x44,0x7c}, // C
  {0x00,0x7c,0x42,0x42,0x42,0x42,0x44,0x78}, // D
  {0x00,0x78,0x40,0x40,0x70,0x40,0x40,0x7c}, // E
  {0x00,0x7c,0x40,0x40,0x78,0x40,0x40,0x40}, // F
  {0x00,0x3c,0x40,0x40,0x5c,0x44,0x44,0x78}, // G
  {0x00,0x42,0x42,0x42,0x7e,0x42,0x42,0x42}, // H
  {0x00,0x7c,0x10,0x10,0x10,0x10,0x10,0x7e}, // I
  {0x00,0x3e,0x08,0x08,0x08,0x48,0x48,0x30}, // J
  {0x00,0x44,0x48,0x50,0x60,0x50,0x48,0x44}, // K
  {0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x7c}, // L
  {0x00,0x82,0xc6,0xaa,0x92,0x82,0x82,0x82}, // M
  {0x00,0x42,0x42,0x62,0x52,0x4a,0x46,0x42}, // N
  {0x00,0x3c,0x42,0x42,0x42,0x42,0x44,0x38}, // O
  {0x00,0x78,0x44,0x44,0x48,0x70,0x40,0x40}, // P
  {0x00,0x3c,0x42,0x42,0x52,0x4a,0x44,0x3a}, // Q
  {0x00,0x78,0x44,0x44,0x78,0x50,0x48,0x44}, // R
  {0x00,0x38,0x40,0x40,0x38,0x04,0x04,0x78}, // S
  {0x00,0x7e,0x90,0x10,0x10,0x10,0x10,0x10}, // T
  {0x00,0x42,0x42,0x42,0x42,0x42,0x42,0x3e}, // U
  {0x00,0x42,0x42,0x42,0x42,0x44,0x28,0x10}, // V
  {0x80,0x82,0x82,0x92,0x92,0x92,0x94,0x78}, // W
  {0x00,0x42,0x42,0x24,0x18,0x24,0x42,0x42}, // X
  {0x00,0x44,0x44,0x28,0x10,0x10,0x10,0x10}, // Y
  {0x00,0x7c,0x04,0x08,0x7c,0x20,0x40,0xfe}, // Z
};
// -----------------------------------------------------------------------------

#define JFONT(c) jennyFont[(c - '0')]
#define JSYM(c)  jennySymbols[(c - ' ')]

// -----------------------------------------------------------------------------

void jennyDemo()
{
  showCharWipe( 8, 0, 3, JFONT('J'), 0, 0 );
  showCharWipe( 8, 0, 4, JFONT('E'), 0, 1 ); 
  showCharWipe( 8, 0, 5, JFONT('N'), 1, 0 ); 
  showCharWipe( 8, 0, 6, JFONT('N'), 1, 1 ); 
  showCharWipe( 8, 0, 7, JFONT('Y'), 0, 0 ); 

  showCharWipe( 8, 1, 5, JSYM(' '), 0, 0 );
  showCharWipe( 8, 1, 5, JSYM('!'), 0, 1 );
  showCharWipe( 8, 1, 5, JSYM(' '), 1, 0 );
  showCharWipe( 8, 1, 5, JSYM('#'), 1, 1 );

  int res = -1;

  int i   = 0;

  while ( res == -1 ) {

    move( 20, 0 );
      printw( "i = '%c', font = %d, %d",
              i + '0',
              sizeof( jennyFont )/sizeof( *jennyFont ),
              sizeof( *jennyFont ) );

    refresh();
    showCharSpiral( 8, 1, 6, jennyFont[i] );

    showCharSpiral( 8, 1, 7, ch_ALL );
    showCharWipe( 8, 1, 7, jennyFont[i], i % 4 / 2, (i % 4) % 2 );

    i++;

    if ( i == ( sizeof( jennyFont ) / sizeof( *jennyFont ) ) ) {
      i = 0;
    }

    refresh();

    timeout( 1000 );
    res = getch();
  }
}

// -----------------------------------------------------------------------------

int main()
{
  //testSpiral();

  initscr();
  curs_set(0);

  // jennyDemo();

  demo();

  endwin();
}


