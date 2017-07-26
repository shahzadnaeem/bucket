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
int TWO_LEDS  = 9;

#define NUMLEDS 5
int leds[ NUMLEDS ] = { 9, 10, 11, 12, 13 };

void writeLeds( int val ) {
  
  for ( int i = 0; i < NUMLEDS; i ++ ) {
     digitalWrite( leds[ i ], val );
  }
}

void redOn() {
  digitalWrite( RED_LED, HIGH );
}

void redOff() {
  digitalWrite( RED_LED, LOW );  
}

void amberOn() {
  digitalWrite( AMBER_LED, HIGH );  
}

void amberOff() {
  digitalWrite( AMBER_LED, LOW );
}

void greenOn() {
  digitalWrite( GREEN_LED, HIGH );
}

void greenOff() {
  digitalWrite( GREEN_LED, LOW );
}


int blueVal = 0;
int blueDelta = 1;

void incBlue() {

  const  int SCALE = 4;
  static int count = SCALE;
  
  if ( count-- ) return;
  
  count = SCALE;
  
  blueVal += blueDelta;
  
  if ( blueVal < 1 ) {
     blueVal   = 2;
     blueDelta = 1;
  }
  
  if ( blueVal > 255 ) {
    blueVal = 254;
    blueDelta = -1;
  }
  
  analogWrite( BLUE_LED, blueVal );
}

void blueOn() {
  digitalWrite( BLUE_LED, HIGH );
}

void blueOff() {
  digitalWrite( BLUE_LED, LOW );
}

int scaleFactor = 1;

void fadeDelay( int t ) {
  
  while ( t >= 0 ) {
    t --;
    t --;
    
    delay( 2 );
    
    incBlue();
  }
}

void myDelay( int t ) {

  int subDelay = 100;
  
  if ( scaleFactor > 0 )
    t = t / scaleFactor;
  else
    t = t * -scaleFactor;
  
  int loops = t / subDelay;

  while ( loops > 0 )
  {  
    digitalWrite( TWO_LEDS, HIGH );
    fadeDelay( subDelay / 2 );
    
    digitalWrite( TWO_LEDS, LOW );
    fadeDelay( subDelay / 2 );
        
    loops --;
  }
}

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for ( int i = 0; i < NUMLEDS; i ++ ) {
    pinMode( leds[ i ], OUTPUT );
  }
  
  Serial.begin( 9600 );
}

// the loop routine runs over and over again forever:
void loop() {

 redOn();
 Serial.println( "Red" );
 myDelay( 3000 );
 
 Serial.println( "Red + Amber" );
 amberOn();
 myDelay( 2000 );
 
 Serial.println( "Green!" );
 redOff();
 amberOff();
 greenOn();
 myDelay( 3000 );
 
 greenOff();
 amberOn();
 myDelay( 1500 );
 
 amberOff();
 
 Serial.print( "Blue: " );
 Serial.print( blueVal, DEC );
 Serial.println( "" );
}

