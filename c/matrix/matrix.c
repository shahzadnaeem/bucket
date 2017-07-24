// -----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
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

      if ( iter.y == size ) {
        printf( "SPLAT!!!\n" );
        endwin();
        exit(1);
      }
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

    usleep( SyncDelay * size );
    refresh();
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

#define FONT(c) font[(c - 'A' + 2)]

int main()
{
  //testSpiral();

  initscr();
  curs_set(0);

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

  int res = -1;
  int i   = 0;

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

  endwin();
}


