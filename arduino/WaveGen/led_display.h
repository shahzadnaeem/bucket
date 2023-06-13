#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include "Arduino.h"
#include <LedControl.h>

// Number of LED matrices
#define DEVICES 1

// LED matrix cell size
#define SIZE 8

// Pins to use
#define LED_DATA 8
#define LED_CLK 9
#define LED_CS 10


extern LedControl lc;

extern unsigned long delaytime;

#define ADD_NOISE 0
#define BOUNDS 0

extern byte font[128][8];

extern void setDisplay(int intensity);
extern void scrollString(int size, int width, const char *string);
extern void fadeDisplay(int times, int start, int fin, int del);
extern void animateString(const char *string, int delayTime);
extern void scrollAnimation();
extern void fastShowChar(int size, byte *ch);
extern void fastShowCharN(int size, int n, byte *ch);

#endif
