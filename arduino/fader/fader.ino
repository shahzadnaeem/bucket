/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

int RED_LED   = 13;
int AMBER_LED = 12;
int GREEN_LED = 11;
int BLUE_LED  = 10;

int RED_LEDS  = 9;

#define NUMLEDS 4
int leds[ NUMLEDS ] = { 10, 11, 12, 13 };

const int MINVAL = 0;
const int MAXVAL = 255;
const int DELAY  = 4;

void writeLeds( int val ) {

  for ( int i = 0; i < NUMLEDS; i ++ ) {
    if ( i % 2 == 1 ) {
      analogWrite( leds[ i ], val );
    } else {
      int newVal = 255 - val;
      
      if ( newVal < MINVAL ) newVal = MINVAL;
      if ( newVal > MAXVAL ) newVal = MAXVAL;
      
      analogWrite( leds[ i ], newVal );
    }
  }
}

const int MAX_LOOPS = 50;
const int MIN_LOOPS = 2;

void toggleRedLeds( int aVal ) {
  
  static int val = !0;

  static int newLoopCount = MIN_LOOPS;
  static int newLoopCountDelta = 1;
  
  static int outerLoopCount = 2 * MAX_LOOPS / newLoopCount;
  static int loopCount      = newLoopCount;

  loopCount --;
    
  if ( loopCount == 0 ) {

    outerLoopCount --;

    if ( outerLoopCount == 0 ) {    
      newLoopCount += newLoopCountDelta;
    
      if ( newLoopCount == MAX_LOOPS ) newLoopCountDelta = -1;
      if ( newLoopCount == MIN_LOOPS ) newLoopCountDelta = 1;
      
      outerLoopCount = 2 * MAX_LOOPS / newLoopCount;
    }
    
    loopCount = newLoopCount;
  } else {
    return;
  }
  
  val = ! val;
  
  if ( val ) {
    digitalWrite( RED_LEDS, HIGH );
  } else {
    digitalWrite( RED_LEDS, LOW );
  }
}

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for ( int i = 0; i < NUMLEDS; i ++ ) {
    pinMode( leds[ i ], OUTPUT );
  }
  
  pinMode( RED_LEDS, OUTPUT );
}

// the loop routine runs over and over again forever:
void loop() {
  
  int val   = MINVAL;
  int delta = 1;
 
  for ( ;; )
  {    
    writeLeds( val );
    
    toggleRedLeds( val );

    if ( ( val == MAXVAL ) || ( val == MINVAL )  ) {
      digitalWrite( RED_LEDS, HIGH );
      delay( 1000 );
    } else {
      delay( DELAY );
    }
  
    if ( val == MAXVAL)  delta = -1;
    if ( val == MINVAL ) delta = 1;
    
    val = val + delta;    
  }
}

