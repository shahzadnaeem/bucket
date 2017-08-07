#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// https://en.wikipedia.org/wiki/Linear-feedback_shift_register

uint32_t prbsGen( uint32_t n, uint32_t mask, int numTaps, int taps[] )
{
  uint32_t xor = 0;

  for ( int i = 0; i < numTaps; i ++ )
  {
    xor = xor ^ ( n >> ( taps[i] - 1 ) );
  }
  
  xor = xor & 1;

  return (( n << 1 ) | xor ) & mask;
}

void prbs( uint32_t mask, int numTaps, int taps[] )
{
  uint32_t start = 0x01;

  uint32_t n = start;

  int i = 1;

  printf( "%u", n );

  do
  {
    n = prbsGen( n, mask, numTaps, taps );

    if ( n != start )
    {
      printf( ", %u", n );
      i ++;
    }
    
  } while ( n != start );

  printf( "\nRepition period = %d\n", i );
}

void prbs6()
{
  int taps[] = { 6, 5 };

  prbs( ( 1 << 6 ) - 1, 2, taps );
}

void prbs12()
{
  int taps[] = { 12, 11, 10, 4 };

  prbs( ( 1 << 12 ) - 1, 4, taps );
}

void prbs19()
{
  int taps[] = { 19, 18, 17, 14 };

  prbs( ( 1 << 19 ) - 1, 4, taps );
}

void prbs6_orig()
{
  uint8_t start = 0x01;
  uint8_t a = start;
  int i;

  printf( "%d", a );

  for(i = 1;; i++) {
    int newbit = (((a >> 5) ^ (a >> 4)) & 1);
    a = ((a << 1) | newbit) & 0x3f;

    //if ( a > 63 ) { i--; continue; }

    if ( a != start )
    {
      printf(", %d", a);
    }
    else
    {
      if (a == start) {
        printf("\nrepetition period is %d\n", i);
        break;
      }
    }
  }
}

int main(int argc, char* argv[]) {

  prbs6();
  prbs6_orig();
  prbs12();
  prbs19();
}
