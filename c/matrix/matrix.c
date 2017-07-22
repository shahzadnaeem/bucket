

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ncurses.h>

int SyncDelay = 20000;

unsigned char chA[] = { 0x00, 0x1c, 0x22, 0x42, 0x42, 0x7e, 0x42, 0x42 };
unsigned char chB[] = { 0x00, 0x78, 0x44, 0x44, 0x78, 0x44, 0x44, 0x7c };
unsigned char ch_[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

typedef struct pos { int x; int y; } pos_t;

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

pos_t lookup( pos_t in )
{
  
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

void showCharSpiral( int size, int y, int x, unsigned char *ch ) {
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

void testSpiral()
{
  int y, x;
  int size = 4;

  for ( int y = 0; y < size; y ++ )
    for ( int x = 0; x < size; x ++ ) {

      pos_t in  = { x, y };
      pos_t out = spiral( size, in );

      printf( "in: (%d,%d) => (%d,%d)\n", in.x, in.y, out.x, out.y );
    }

  exit(1);
}

int main()
{
  int i, j;

  testSpiral();

  initscr();

  showChar( 8, 1, 3, chA );
  showChar( 8, 1, 4, chB );
  showCharSpiral( 8, 1, 3, chB );

  refresh();

  getch();

  endwin();
}


