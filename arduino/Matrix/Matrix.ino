#include <LedControl.h>

// Number of LED matrices
#define DEVICES 4

// LED matrix cell size
#define SIZE 8

LedControl lc=LedControl(2,3,4, DEVICES);

unsigned long delaytime = 100;

void setup() {

  Serial.begin(115200);

  for ( int d = 0; d < DEVICES; d ++ ) {
    // Wake up  
    lc.shutdown(d,false);

    // Med brighness
    lc.setIntensity(d,1+d*d);

    // Clear
    lc.clearDisplay(d);
  }
}

byte font[128][8] = 
{
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0000
  { 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0001
  { 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0002
  { 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0003
  { 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00 },  // 0004
  { 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00 },  // 0005
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00 },  // 0006
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00 },  // 0007
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff },  // 0008
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00 },  // 0009
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00 },  // 000a
  { 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00 },  // 000b
  { 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00 },  // 000c
  { 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 000d
  { 0x00, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 000e
  { 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 000f
  { 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00 },  // 0010
  { 0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00, 0x00 },  // 0011
  { 0x00, 0x18, 0x3c, 0x7e, 0x73, 0x3c, 0x18, 0x00 },  // 0012
  { 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x3c, 0x18 },  // 0013
  { 0x18, 0x24, 0x42, 0x81, 0x81, 0x42, 0x24, 0x18 },  // 0014
  { 0x00, 0x18, 0x24, 0x42, 0x42, 0x24, 0x18, 0x00 },  // 0015
  { 0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00 },  // 0016
  { 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00 },  // 0017
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0018
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0019
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 001a
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 001b
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 001c
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 001d
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 001e
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 001f
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0020
  { 0x18, 0x3c, 0x3c, 0x18, 0x18, 0x00, 0x18, 0x00 },  // 0021
  { 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0022
  { 0x6c, 0x6c, 0xfe, 0x6c, 0xfe, 0x6c, 0x6c, 0x00 },  // 0023
  { 0x30, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x30, 0x00 },  // 0024
  { 0x00, 0xc6, 0xcc, 0x18, 0x30, 0x66, 0xc6, 0x00 },  // 0025
  { 0x38, 0x6c, 0x38, 0x76, 0xdc, 0xcc, 0x76, 0x00 },  // 0026
  { 0x60, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0027
  { 0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00 },  // 0028
  { 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00 },  // 0029
  { 0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00, 0x00 },  // 002a
  { 0x00, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x00, 0x00 },  // 002b
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x60 },  // 002c
  { 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00 },  // 002d
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00 },  // 002e
  { 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00 },  // 002f
  { 0x7c, 0xc6, 0xce, 0xde, 0xf6, 0xe6, 0x7c, 0x00 },  // 0030
  { 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x00 },  // 0031
  { 0x78, 0xcc, 0x0c, 0x38, 0x60, 0xcc, 0xfc, 0x00 },  // 0032
  { 0x78, 0xcc, 0x0c, 0x38, 0x0c, 0xcc, 0x78, 0x00 },  // 0033
  { 0x1c, 0x3c, 0x6c, 0xcc, 0xfe, 0x0c, 0x1e, 0x00 },  // 0034
  { 0xfc, 0xc0, 0xf8, 0x0c, 0x0c, 0xcc, 0x78, 0x00 },  // 0035
  { 0x38, 0x60, 0xc0, 0xf8, 0xcc, 0xcc, 0x78, 0x00 },  // 0036
  { 0xfc, 0xcc, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x00 },  // 0037
  { 0x78, 0xcc, 0xcc, 0x78, 0xcc, 0xcc, 0x78, 0x00 },  // 0038
  { 0x78, 0xcc, 0xcc, 0x7c, 0x0c, 0x18, 0x70, 0x00 },  // 0039
  { 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00 },  // 003a
  { 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x60 },  // 003b
  { 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x00 },  // 003c
  { 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00 },  // 003d
  { 0x60, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x60, 0x00 },  // 003e
  { 0x78, 0xcc, 0x0c, 0x18, 0x30, 0x00, 0x30, 0x00 },  // 003f
  { 0x7c, 0xc6, 0xde, 0xde, 0xde, 0xc0, 0x78, 0x00 },  // 0040
  { 0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00 },  // 0041
  { 0xfc, 0x66, 0x66, 0x7c, 0x66, 0x66, 0xfc, 0x00 },  // 0042
  { 0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00 },  // 0043
  { 0xf8, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0xf8, 0x00 },  // 0044
  { 0xfe, 0x62, 0x68, 0x78, 0x68, 0x62, 0xfe, 0x00 },  // 0045
  { 0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0xf0, 0x00 },  // 0046
  { 0x3c, 0x66, 0xc0, 0xc0, 0xce, 0x66, 0x3e, 0x00 },  // 0047
  { 0xcc, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0xcc, 0x00 },  // 0048
  { 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 },  // 0049
  { 0x1e, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78, 0x00 },  // 004a
  { 0xe6, 0x66, 0x6c, 0x78, 0x6c, 0x66, 0xe6, 0x00 },  // 004b
  { 0xf0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x00 },  // 004c
  { 0xc6, 0xee, 0xfe, 0xfe, 0xd6, 0xc6, 0xc6, 0x00 },  // 004d
  { 0xc6, 0xe6, 0xf6, 0xde, 0xce, 0xc6, 0xc6, 0x00 },  // 004e
  { 0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00 },  // 004f
  { 0xfc, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xf0, 0x00 },  // 0050
  { 0x78, 0xcc, 0xcc, 0xcc, 0xdc, 0x78, 0x1c, 0x00 },  // 0051
  { 0xfc, 0x66, 0x66, 0x7c, 0x6c, 0x66, 0xe6, 0x00 },  // 0052
  { 0x78, 0xcc, 0xe0, 0x70, 0x1c, 0xcc, 0x78, 0x00 },  // 0053
  { 0xfc, 0xb4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 },  // 0054
  { 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xfc, 0x00 },  // 0055
  { 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00 },  // 0056
  { 0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6, 0x00 },  // 0057
  { 0xc6, 0xc6, 0x6c, 0x38, 0x38, 0x6c, 0xc6, 0x00 },  // 0058
  { 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x30, 0x78, 0x00 },  // 0059
  { 0xfe, 0xc6, 0x8c, 0x18, 0x32, 0x66, 0xfe, 0x00 },  // 005a
  { 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00 },  // 005b
  { 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02, 0x00 },  // 005c
  { 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00 },  // 005d
  { 0x10, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00 },  // 005e
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff },  // 005f
  { 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0060
  { 0x00, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x76, 0x00 },  // 0061
  { 0xe0, 0x60, 0x60, 0x7c, 0x66, 0x66, 0xdc, 0x00 },  // 0062
  { 0x00, 0x00, 0x78, 0xcc, 0xc0, 0xcc, 0x78, 0x00 },  // 0063
  { 0x1c, 0x0c, 0x0c, 0x7c, 0xcc, 0xcc, 0x76, 0x00 },  // 0064
  { 0x00, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00 },  // 0065
  { 0x38, 0x6c, 0x60, 0xf0, 0x60, 0x60, 0xf0, 0x00 },  // 0066
  { 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8 },  // 0067
  { 0xe0, 0x60, 0x6c, 0x76, 0x66, 0x66, 0xe6, 0x00 },  // 0068
  { 0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00 },  // 0069
  { 0x0c, 0x00, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78 },  // 006a
  { 0xe0, 0x60, 0x66, 0x6c, 0x78, 0x6c, 0xe6, 0x00 },  // 006b
  { 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 },  // 006c
  { 0x00, 0x00, 0xcc, 0xfe, 0xfe, 0xd6, 0xc6, 0x00 },  // 006d
  { 0x00, 0x00, 0xf8, 0xcc, 0xcc, 0xcc, 0xcc, 0x00 },  // 006e
  { 0x00, 0x00, 0x78, 0xcc, 0xcc, 0xcc, 0x78, 0x00 },  // 006f
  { 0x00, 0x00, 0xdc, 0x66, 0x66, 0x7c, 0x60, 0xf0 },  // 0070
  { 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0x1e },  // 0071
  { 0x00, 0x00, 0xdc, 0x76, 0x66, 0x60, 0xf0, 0x00 },  // 0072
  { 0x00, 0x00, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x00 },  // 0073
  { 0x10, 0x30, 0x7c, 0x30, 0x30, 0x34, 0x18, 0x00 },  // 0074
  { 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x00 },  // 0075
  { 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00 },  // 0076
  { 0x00, 0x00, 0xc6, 0xd6, 0xfe, 0xfe, 0x6c, 0x00 },  // 0077
  { 0x00, 0x00, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0x00 },  // 0078
  { 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8 },  // 0079
  { 0x00, 0x00, 0xfc, 0x98, 0x30, 0x64, 0xfc, 0x00 },  // 007a
  { 0x1c, 0x30, 0x30, 0xe0, 0x30, 0x30, 0x1c, 0x00 },  // 007b
  { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00 },  // 007c
  { 0xe0, 0x30, 0x30, 0x1c, 0x30, 0x30, 0xe0, 0x00 },  // 007d
  { 0x76, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 007e
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }   // 007f
};

struct pos { int x; int y; };

struct pos spiral( int size, struct pos in )
{
  struct pos out  = { size / 2, size / 2 - 1 };
  struct pos iter = { 0, 0 };

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

void testSpiral()
{
  int y, x;
  int size = 4;

  for ( int y = 0; y < size; y ++ )
    for ( int x = 0; x < size; x ++ ) {

      struct pos in  = { x, y };
      struct pos out = spiral( size, in );

      Serial.print( "in: ");
      Serial.print( in.x );
      Serial.print( ", " );
      Serial.print( in.y );
      Serial.print( " => " );
      Serial.print( out.x );
      Serial.print( ", " );
      Serial.println( out.y );
    }
}

void showCharN( int size, int n, byte *ch )
{
  int x, y;

  for ( y = 0; y < size; y ++ ) {
    for ( x = 0; x < size; x ++ ) {
      byte mask = 1 << ( size - 1 - x );

      lc.setLed(n, y, x, ch[y] & mask );
    }
  }  
}

void showChar( int size, byte *ch ) {
  showCharN( size, 0, ch );
}

void fastShowCharN( int size, int n, byte *ch )
{
  int r;

  for ( r = 0; r < size; r ++ )
  {
    lc.setRow( n, r, ch[r] );
  }
}

void fastShowChar( int size, byte *ch )
{
  fastShowCharN( 0, size, ch );
}

void setBit( int n, int y, int x, int b )
{
  lc.setLed(n, y, x, 1 );
  delay( delaytime / 50 );
  lc.setLed(n, y, x, b );
}

void showCharSpiralN( int size, int n, byte *ch )
{
  for ( int y = 0; y < size; y ++ ) {

    for ( int x = 0; x < size; x ++ ) {

      struct pos in = { x, y };

      struct pos out = spiral( size, in );

      byte mask = 1 << ( size - 1 - out.x );

      setBit( n, out.y, out.x, ch[out.y] & mask );
    }
  }
}

void showCharSpiral( int size, byte *ch )
{
  showCharSpiralN( size, 0, ch );
}

void showCharWipeN( int size, int n, int y, int x, unsigned char *ch, int vert, int dir )
{
  for ( int i = 0; i < size; i ++ ) {
    for ( int j = 0; j < size; j ++ ) {

      unsigned char mask;
      unsigned char bit;

      if ( vert ) {
        if ( dir ) {
          mask = 1 << ( size - 1 - i );
          bit = ch[ j ] & mask;
          setBit( n, j, i, bit );
        } else {
          mask = 1 << ( i );
          bit = ch[ j ] & mask;
          setBit( n, j, size - 1 - i, bit );
        }
      } else {
        if ( dir ) {
          mask = 1 << ( size - 1 - j );
          bit = ch[ i ] & mask;
          setBit( n, i, j, bit );
        } else {
          mask = 1 << ( j );
          bit = ch[ size - 1 - i ] & mask;
          setBit( n, size - 1 - i, size - 1 - j, bit );
        }
      }
    }
  }
}

void showCharWipe( int size, int n, int y, int x, unsigned char *ch, int vert, int dir )
{
  showCharWipeN( size, 0, y, x, ch, vert, dir );
}

void writeArduinoOnMatrix()
{
  int i, j, b;

  //lc.setIntensity(0,12);

  for ( i = 32; i < 128; i ++ ) {
    for ( int n = 0; n < DEVICES; n ++ ) {
      showCharSpiralN( SIZE, n, font[i] );
    }
    delay( delaytime * 10 );
    
    for ( int n = 0; n < DEVICES; n ++ ) {
      showCharN( SIZE, n, font[0] );
    }
    delay( delaytime );
    
    for ( int n = 0; n < DEVICES; n ++ ) {
      showCharWipeN( SIZE, n, 1, 7, font[i], i % 4 / 2, (i % 4) % 2 );
    }
    delay( delaytime * 10 );
  }
}

void bigCounter() {

  unsigned char big[SIZE];

  int i;

  for ( i = 0; i < SIZE; i ++ ) {
    big[i] = 0;
  }

  //lc.setIntensity(0,15);

  while (1) {

    int i = 0;
    while ( i < SIZE && ( ++big[i++] == 0 ));

    for ( int n = 0; n < DEVICES; n ++ ) {
      fastShowCharN( SIZE, n, big );
    }

    //delay( delaytime );
  }
}

void showScroll( int size, int pos, int n, byte *ch1, byte *ch2 )
{
  byte newChar[size];

  for ( int i = 0; i < size; i ++ ) {
    newChar[i] = ( ( ch1[i] << pos ) | ( ch2[i] >> ( size - pos ) ) );
 }

  fastShowCharN( SIZE, n, newChar );
}

void showScrollAnimation( int size, int frames, int pos, byte *ch1[], byte *ch2[] )
{
  byte newChar[size];

  int frame = pos % frames;

  for ( int i = 0; i < size; i ++ ) {
    newChar[i] = ( ( ch1[frame][i] << pos ) | ( ch2[frame][i] >> ( size - pos ) ) );
 }

  fastShowChar( SIZE, newChar );  
}

void scrollAnimation()
{
  byte *ch1[] = { font['a'], font['b'] };
  byte *ch2[] = { font['A'], font['B'] };

  for ( int p = 0; p < SIZE; p ++ ) {
    showScrollAnimation( SIZE, 2, p, ch1, ch2 );
    delay( 10 * delaytime );
  }
}

void scrollString( int size, int width, const char *string )
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
        showScroll( size, p, width - j - 1, font[string[i+j]], font[string[i+j+1]] );
      }
      delay( delaytime );
    }

    i ++;
  } while ( i < lastPos );
}

void animateString( const char *string, int delayTime )
{
  int len = strlen( string );

  for ( int i = 0; i <len; i ++ ) {
    for ( int n = 0; n < DEVICES; n ++ ) {
      fastShowCharN( SIZE, n, font[string[i]] );
    }
    delay( delayTime );
  }
}

void nowServing()
{
  int now = 100;

  do
  {
    char msg[60];

    sprintf( msg, "   Now serving:%d", now );

    scrollString( SIZE, DEVICES, msg );

    int del = random( 10 ) + 1;
    delay( 1000 * del );

    if ( random( 10 ) <= 2 ) {
      now += ( random( 3 ) + 1 );
    }

    now ++;
    
  } while ( true );
}


void loop() {

  lc.clearDisplay(0);

  //testSpiral();

  //bigCounter();

  //nowServing();
  
  scrollString( SIZE, DEVICES, "Hello there Jenny, hello there Iman!" );

  //scrollAnimation();

  if ( 0 ) {
  for ( int i = 1; i < 20; i ++ ) {
    char buf[20];

    sprintf( buf, " d=%dms ", i );
    scrollString( SIZE, DEVICES, buf );

    const char *msg = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0d\x0e\x0f";
    int len = strlen( msg );
    const char *msg2 = "\x10\x11\x12\x13\x14\x15\x16\x17";

    int d = i * 10;
    int j = 1000 / ( d * len );

    do {
      //animateString( msg, d );

      animateString( msg2, d );

      j --;
    } while ( j >= 0 );
  }
  }

  //writeArduinoOnMatrix();
}

