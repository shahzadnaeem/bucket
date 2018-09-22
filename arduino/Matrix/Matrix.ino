#include <LedControl.h> 
#include <DHT.h>

/* #define __DUE__ */
#ifdef __DUE__
#include <DueTimer.h>
#endif

// Number of LED matrices
#define DEVICES 1

// LED matrix cell size
#define SIZE 8

#define LED_DATA 8
#define LED_CLK  9
#define LED_CS   10

LedControl lc=LedControl(LED_DATA, LED_CLK, LED_CS, DEVICES);

#define TEMP_DATA 6

DHT dht( TEMP_DATA, DHT11 );

#define PIR_DATA 2
#define PIR_SHOW_LED 13

unsigned long delaytime = 100;

#define ADD_NOISE 0

#define BOUNDS 0

void setup() {

  Serial.begin(115200);

  pinMode( PIR_DATA, INPUT );
  pinMode( PIR_SHOW_LED, OUTPUT );

  for ( int d = 0; d < DEVICES; d ++ ) {
    // Wake up  
    lc.shutdown(d,false);

    // Med brighness
    lc.setIntensity(d,12);

    // Fade brigthness
    //lc.setIntensity(d,1+d*d);

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
  { 0x00, 0x18, 0x3c, 0x7e, 0x7e, 0x3c, 0x18, 0x00 },  // 0012
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
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0020 ' '
  { 0x18, 0x3c, 0x3c, 0x18, 0x18, 0x00, 0x18, 0x00 },  // 0021 '!'
  { 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0022 '"'
  { 0x6c, 0x6c, 0xfe, 0x6c, 0xfe, 0x6c, 0x6c, 0x00 },  // 0023 '#'
  { 0x30, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x30, 0x00 },  // 0024 '$'
  { 0x00, 0xc6, 0xcc, 0x18, 0x30, 0x66, 0xc6, 0x00 },  // 0025 '%'
  { 0x38, 0x6c, 0x38, 0x76, 0xdc, 0xcc, 0x76, 0x00 },  // 0026 '&'
  { 0x60, 0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0027 '''
  { 0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00 },  // 0028 '('
  { 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00 },  // 0029 ')'
  { 0x00, 0x66, 0x3c, 0xff, 0x3c, 0x66, 0x00, 0x00 },  // 002a '*'
  { 0x00, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x00, 0x00 },  // 002b '+'
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x60 },  // 002c ','
  { 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00 },  // 002d '-'
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00 },  // 002e '.'
  { 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00 },  // 002f '/'
  { 0x7c, 0xc6, 0xce, 0xde, 0xf6, 0xe6, 0x7c, 0x00 },  // 0030 '0'
  { 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x00 },  // 0031 '1'
  { 0x78, 0xcc, 0x0c, 0x38, 0x60, 0xcc, 0xfc, 0x00 },  // 0032 '2'
  { 0x78, 0xcc, 0x0c, 0x38, 0x0c, 0xcc, 0x78, 0x00 },  // 0033 '3'
  { 0x1c, 0x3c, 0x6c, 0xcc, 0xfe, 0x0c, 0x1e, 0x00 },  // 0034 '4'
  { 0xfc, 0xc0, 0xf8, 0x0c, 0x0c, 0xcc, 0x78, 0x00 },  // 0035 '5'
  { 0x38, 0x60, 0xc0, 0xf8, 0xcc, 0xcc, 0x78, 0x00 },  // 0036 '6'
  { 0xfc, 0xcc, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x00 },  // 0037 '7'
  { 0x78, 0xcc, 0xcc, 0x78, 0xcc, 0xcc, 0x78, 0x00 },  // 0038 '8'
  { 0x78, 0xcc, 0xcc, 0x7c, 0x0c, 0x18, 0x70, 0x00 },  // 0039 '9'
  { 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00 },  // 003a ':'
  { 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x60 },  // 003b ';'
  { 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x00 },  // 003c '<'
  { 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00 },  // 003d '='
  { 0x60, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x60, 0x00 },  // 003e '>'
  { 0x78, 0xcc, 0x0c, 0x18, 0x30, 0x00, 0x30, 0x00 },  // 003f '?'
  { 0x7c, 0xc6, 0xde, 0xde, 0xde, 0xc0, 0x78, 0x00 },  // 0040 '@'
  { 0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00 },  // 0041 'A'
  { 0xfc, 0x66, 0x66, 0x7c, 0x66, 0x66, 0xfc, 0x00 },  // 0042 'B'
  { 0x3c, 0x66, 0xc0, 0xc0, 0xc0, 0x66, 0x3c, 0x00 },  // 0043 'C'
  { 0xf8, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0xf8, 0x00 },  // 0044 'D'
  { 0xfe, 0x62, 0x68, 0x78, 0x68, 0x62, 0xfe, 0x00 },  // 0045 'E'
  { 0xfe, 0x62, 0x68, 0x78, 0x68, 0x60, 0xf0, 0x00 },  // 0046 'F'
  { 0x3c, 0x66, 0xc0, 0xc0, 0xce, 0x66, 0x3e, 0x00 },  // 0047 'G'
  { 0xcc, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0xcc, 0x00 },  // 0048 'H'
  { 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 },  // 0049 'I'
  { 0x1e, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78, 0x00 },  // 004a 'J'
  { 0xe6, 0x66, 0x6c, 0x78, 0x6c, 0x66, 0xe6, 0x00 },  // 004b 'K'
  { 0xf0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xfe, 0x00 },  // 004c 'L'
  { 0xc6, 0xee, 0xfe, 0xfe, 0xd6, 0xc6, 0xc6, 0x00 },  // 004d 'M'
  { 0xc6, 0xe6, 0xf6, 0xde, 0xce, 0xc6, 0xc6, 0x00 },  // 004e 'N'
  { 0x38, 0x6c, 0xc6, 0xc6, 0xc6, 0x6c, 0x38, 0x00 },  // 004f 'O'
  { 0xfc, 0x66, 0x66, 0x7c, 0x60, 0x60, 0xf0, 0x00 },  // 0050 'P'
  { 0x78, 0xcc, 0xcc, 0xcc, 0xdc, 0x78, 0x1c, 0x00 },  // 0051 'Q'
  { 0xfc, 0x66, 0x66, 0x7c, 0x6c, 0x66, 0xe6, 0x00 },  // 0052 'R'
  { 0x78, 0xcc, 0xe0, 0x70, 0x1c, 0xcc, 0x78, 0x00 },  // 0053 'S'
  { 0xfc, 0xb4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 },  // 0054 'T'
  { 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xfc, 0x00 },  // 0055 'U'
  { 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00 },  // 0056 'V'
  { 0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6, 0x00 },  // 0057 'W'
  { 0xc6, 0xc6, 0x6c, 0x38, 0x38, 0x6c, 0xc6, 0x00 },  // 0058 'X'
  { 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x30, 0x78, 0x00 },  // 0059 'Y'
  { 0xfe, 0xc6, 0x8c, 0x18, 0x32, 0x66, 0xfe, 0x00 },  // 005a 'Z'
  { 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00 },  // 005b '['
  { 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02, 0x00 },  // 005c '\'
  { 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00 },  // 005d ']'
  { 0x10, 0x38, 0x6c, 0xc6, 0x00, 0x00, 0x00, 0x00 },  // 005e '^'
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff },  // 005f '_'
  { 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 0060 '`'
  { 0x00, 0x00, 0x78, 0x0c, 0x7c, 0xcc, 0x76, 0x00 },  // 0061 'a'
  { 0xe0, 0x60, 0x60, 0x7c, 0x66, 0x66, 0xdc, 0x00 },  // 0062 'b'
  { 0x00, 0x00, 0x78, 0xcc, 0xc0, 0xcc, 0x78, 0x00 },  // 0063 'c'
  { 0x1c, 0x0c, 0x0c, 0x7c, 0xcc, 0xcc, 0x76, 0x00 },  // 0064 'd'
  { 0x00, 0x00, 0x78, 0xcc, 0xfc, 0xc0, 0x78, 0x00 },  // 0065 'e'
  { 0x38, 0x6c, 0x60, 0xf0, 0x60, 0x60, 0xf0, 0x00 },  // 0066 'f'
  { 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8 },  // 0067 'g'
  { 0xe0, 0x60, 0x6c, 0x76, 0x66, 0x66, 0xe6, 0x00 },  // 0068 'h'
  { 0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00 },  // 0069 'i'
  { 0x0c, 0x00, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x78 },  // 006a 'j'
  { 0xe0, 0x60, 0x66, 0x6c, 0x78, 0x6c, 0xe6, 0x00 },  // 006b 'k'
  { 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00 },  // 006c 'l'
  { 0x00, 0x00, 0xcc, 0xfe, 0xfe, 0xd6, 0xc6, 0x00 },  // 006d 'm'
  { 0x00, 0x00, 0xf8, 0xcc, 0xcc, 0xcc, 0xcc, 0x00 },  // 006e 'n'
  { 0x00, 0x00, 0x78, 0xcc, 0xcc, 0xcc, 0x78, 0x00 },  // 006f 'o'
  { 0x00, 0x00, 0xdc, 0x66, 0x66, 0x7c, 0x60, 0xf0 },  // 0070 'p'
  { 0x00, 0x00, 0x76, 0xcc, 0xcc, 0x7c, 0x0c, 0x1e },  // 0071 'q'
  { 0x00, 0x00, 0xdc, 0x76, 0x66, 0x60, 0xf0, 0x00 },  // 0072 'r'
  { 0x00, 0x00, 0x7c, 0xc0, 0x78, 0x0c, 0xf8, 0x00 },  // 0073 's'
  { 0x10, 0x30, 0x7c, 0x30, 0x30, 0x34, 0x18, 0x00 },  // 0074 't'
  { 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0xcc, 0x76, 0x00 },  // 0075 'u'
  { 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x78, 0x30, 0x00 },  // 0076 'v'
  { 0x00, 0x00, 0xc6, 0xd6, 0xfe, 0xfe, 0x6c, 0x00 },  // 0077 'w'
  { 0x00, 0x00, 0xc6, 0x6c, 0x38, 0x6c, 0xc6, 0x00 },  // 0078 'x'
  { 0x00, 0x00, 0xcc, 0xcc, 0xcc, 0x7c, 0x0c, 0xf8 },  // 0079 'y'
  { 0x00, 0x00, 0xfc, 0x98, 0x30, 0x64, 0xfc, 0x00 },  // 007a 'z'
  { 0x1c, 0x30, 0x30, 0xe0, 0x30, 0x30, 0x1c, 0x00 },  // 007b '{'
  { 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00 },  // 007c '|'
  { 0xe0, 0x30, 0x30, 0x1c, 0x30, 0x30, 0xe0, 0x00 },  // 007d '}'
  { 0x76, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // 007e '~'
  { 0x60, 0x90, 0x90, 0x66, 0x09, 0x08, 0x09, 0x06 }   // 007f
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
    byte noise = 0;

    if ( ADD_NOISE )
    {
      noise = ( random( ADD_NOISE ) & random( ADD_NOISE ) & random( ADD_NOISE ) & random( ADD_NOISE ) ) & 0xFF;
    }

    byte c = ch[r] ^ noise;

    if ( BOUNDS )
    {
      if ( r == 0 || r == 7 ) c = c | 0x81;  
    }

    lc.setRow( n, r, c );
  }
}

void fastShowChar( int size, byte *ch )
{
  fastShowCharN( size, 0, ch );
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

#ifdef __DUE__
long fire = 0;

void fireNow()
{
  fire = 1;
}

int setupTimer( long t )
{
  Timer3.attachInterrupt( fireNow ).start( t );

  return 1;
}
#else
long fire = 1;

int setupTimer( long t )
{
  return 0;
}
#endif

void bigCounter() {

  unsigned char big[SIZE];

  int i;

  for ( i = 0; i < SIZE; i ++ ) {
    big[i] = 0;
  }

  int haveTimer = setupTimer( 1000000 / 25 );
  
  //lc.setIntensity(0,15);

  long n = 0;

  while (1) {
    int i = 0;
    while ( i < SIZE && ( ++big[i++] == 0 ));

    n++;

    if ( fire ) {
      for ( int n = 0; n < DEVICES; n ++ ) {
        fastShowCharN( SIZE, n, big );
      }

      if ( haveTimer ) fire = 0;
    }

    if ( ! haveTimer ) delay( delaytime );
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
  byte *ch1[] = { font[0x10], font[0x11], font[0x12], font[0x13], font[0x14], font[0x15], font[0x16] };
  byte *ch2[] = { font[0x10], font[0x11], font[0x12], font[0x13], font[0x14], font[0x15], font[0x16] };

  for ( int p = 0; p < SIZE; p ++ ) {
    showScrollAnimation( SIZE, 7, p, ch1, ch2 );

    //showScroll( SIZE, p, 0, ch1[0], ch2[0] );

    delay( 60 );
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

  if ( len > width ) {
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

  // Final position
  for ( int j = 0; j < width; j ++ ) {
    showScroll( size, 0, width - j - 1, font[string[len-(width-j)]], font[string[len-(width-j)]] );    
  }
  delay( delaytime );
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

int limit( int v, int min, int max )
{
  if ( v < min ) return min;
  if ( v > max ) return max;
  return v;
}

void setDisplay( int intensity )
{
  for ( int d = 0; d <= DEVICES; d ++ )
  {
    lc.setIntensity( d, intensity );   
  }
}

void fadeDisplay( int times, int start, int fin, int del )
{
  int s = limit( start, 0, 15 );
  int e = limit( fin, 0, 15 );

  if ( times % 2 == 1 ) times ++;

  for ( int t = 0; t < times; t ++ )
  {
    int inc = 1;
    
    if ( s > e ) inc = -1; 
    
    for ( int b = s; b != e; b = b + inc ) {
      for ( int d = 0; d <= DEVICES; d ++ )
      {
        lc.setIntensity( d, b );   
      }
      delay( del );
    }

    int tmp = s;
    s = e;
    e = tmp;
  }
}

void nowServing()
{
  int now = 100;

  int intensity = 12;

  do
  {
    char msg[60];

    sprintf( msg, "    ... Now serving>%3d", now );

    setDisplay( intensity );

    scrollString( SIZE, DEVICES, msg );

    int del = random( 3 ) * 3 + 1;

    int inc = 1;

    if ( random( 10 ) <= 3 ) {
      inc += ( random( 3 ) + 1 );
    }

    fadeDisplay( del * inc, intensity, 1, 80 );

    now += inc;

    if ( now > 999 ) {
      now = 42;
    }

  } while ( true );
}


void phpIs()
{
  char *whats[] =
  {
    "Shit",
    "ACE!",
    "Okay",
    "Duff"  
  };

  int delayTime = 2000;

  int numWhats = sizeof( whats ) / sizeof( *whats );

  char msg[64];

  sprintf( msg, "PHP is ..." );
  scrollString( SIZE, DEVICES, msg );
  delay( delayTime );

  int what = random( numWhats );
  scrollString( SIZE, DEVICES, whats[what] );
  delay( delayTime );
  
}


void tempAndHumidity()
{
  const int oneSec = 1000;
  const int preReadDelay = 2 * oneSec;

  delay( preReadDelay );

  dht.read();

  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  char msg[64];

  if ( isnan( temp ) || isnan(humidity) )
  {
    sprintf( msg, "Bad read!" );
    scrollString( SIZE, DEVICES, msg );
  } else {
    sprintf( msg, "t=%2.0f\x7f", temp );
    scrollString( SIZE, DEVICES, msg );
    delay(oneSec);
    sprintf( msg, "h=%2.0f%%", humidity );
    scrollString( SIZE, DEVICES, msg );
  }
  delay(oneSec);
}

void animationTest()
{
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
      animateString( msg, d );

      animateString( msg2, d );

      j --;
    } while ( j >= 0 );
  }
}

void scrollAnimationLoop( int n )
{
  for ( int l = 0; l <= n; l ++ ) {
    scrollAnimation();
  }
}

#define SET_CELL( b, x, y ) b[y] = b[y] | ( 1 << ( SIZE - x - 1 ) )
#define CLR_CELL( b, x, y ) b[y] = b[y] & ( ~( 1 << ( SIZE - x - 1 ) ) & 0xFF )
#define CELL_ISSET( b, x, y ) ( ( b[y] & ( 1 << ( SIZE - x - 1 ) ) ) != 0 )

int lifeBoardEmpty( byte b[8] )
{
  for ( int i = 0; i < SIZE; i ++ )
  {
    if ( b[i] ) return 0;
  }

  return 1;
}

int lifeBoardCopy( byte from[8], byte to[8] )
{
  for ( int i = 0; i < SIZE; i ++ )
  {
    to[i] = from[i];
  }
}

int lifeBoardsSame( byte b1[8], byte b2[8] ) {
  
  for ( int i = 0; i < SIZE; i ++ )
  {
    if ( b1[i] != b2[i] ) return 0;
  }

  return 1;
}

int lifeNeighbours( byte b[8], int x, int y )
{
  int res = 0;

  for ( int r = y - 1; r < y + 2; r ++ ) {
    for ( int c = x - 1; c < x + 2; c++ ) {
      if ( ( r >= 0 && r < SIZE ) && ( c >= 0 && c < SIZE ) ) {
        if ( CELL_ISSET( b, c, r ) ) {
          res ++;
        }
      }
    }
  }

  if ( CELL_ISSET( b, x, y ) ) {
    res --;
  }

  return res;
}

void gameOfLife()
{
  byte b[8] =  { 0, 0, 0x70, 0, 0, 0x07, 0, 0 };
  byte oldB[8];

  for ( int i = 0; i < SIZE; i ++ )
  {
    //SET_CELL( b, i, i );

    b[i] = random( 256 );
  }

  fastShowChar( SIZE, b );

  delay( 1000 );

  int iterations = 100;
  int done = 0;

  while ( !done && !lifeBoardEmpty( b ) && iterations )
  {
    lifeBoardCopy( b, oldB );

    for ( int y = 0; y < SIZE; y ++ ) {
      for ( int x = 0; x < SIZE; x ++ ) {
        int nbs = lifeNeighbours( oldB, x, y );
        int live = CELL_ISSET( oldB, x, y );

        if ( live ) {
          if ( ( nbs < 2 ) || ( nbs > 3 ) ) {
            CLR_CELL( b, x, y );
          }
        } else {
          if ( nbs == 3 ) {
            SET_CELL( b, x, y );
          }
        }
      }
    }

    fastShowChar( SIZE, b );

    delay( 60 );

    done = lifeBoardsSame( b, oldB );
    
    iterations --;
  }

  delay( 1000 );


  int setCount = 0;

  for ( int y = 0; y < SIZE; y ++ ) {
    for ( int x = 0; x < SIZE; x ++ ) {
      if ( CELL_ISSET( b, x, y ) ) {
        setCount ++;
      }
    }
  }

  char msg[65];
  sprintf( msg, "#=%d i=%d", setCount, 100-iterations );
  scrollString( SIZE, DEVICES, msg );

  delay( 1000 );
}

void checkPir()
{
  int delayTime = 20;
  int pirRead;

  pirRead = digitalRead( PIR_DATA );
  
  if ( pirRead ) {
    digitalWrite( PIR_SHOW_LED, HIGH );
  } else {
    digitalWrite( PIR_SHOW_LED, LOW );    
  }

  if ( pirRead ) {
    fastShowChar( SIZE, font['Y'] );
  } else {
    fastShowChar( SIZE, font['N'] );  
  }

  delay( delayTime );
}

void loop() {

  checkPir();

  //testSpiral();

  //bigCounter();

  //nowServing();
  
  //scrollString( SIZE, DEVICES, "Hello there Jenny, hello there Iman!, Yo POPS :)" );

  tempAndHumidity();

  //scrollAnimationLoop( 10 );

  //phpIs();

  //animationTest();

  //gameOfLife();

  //writeArduinoOnMatrix();
}

