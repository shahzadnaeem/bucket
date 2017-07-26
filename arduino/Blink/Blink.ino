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

#define NUMLEDS 3
int leds[ NUMLEDS ] = { 11, 12, 13 };

void writeLeds( int val ) {
  
  for ( int i = 0; i < NUMLEDS; i ++ ) {
     digitalWrite( leds[ i ], val );
  }
}

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for ( int i = 0; i < NUMLEDS; i ++ ) {
    pinMode( leds[ i ], OUTPUT);
  }
}

// the loop routine runs over and over again forever:
void loop() {
 
  for ( int i = 0; i < 10; i ++ )
  {    
    writeLeds( HIGH );
    delay(5);
  
    writeLeds( LOW );
    delay(500);
  }
  
  for ( int j = 0; j < 1000; j ++ )
  {
    writeLeds( HIGH );
    delay(1);
  
    writeLeds( LOW );
    delay(1);
  }
}
