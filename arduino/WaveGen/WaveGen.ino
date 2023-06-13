
#include "MCP4725.h"
#include "Wire.h"
#include <DHT.h>

#include "led_display.h"
#include "wave_data.h"

// DUE Timer optimisation - TODO: Factor this out and verify behaviour

#define __DUE__
#ifdef __DUE__
#include <DueTimer.h>
#endif

#ifdef __DUE__
long fire = 0;

void fireNow()
{
    fire = 1;
}

int setupTimer(long t)
{
    Timer3.attachInterrupt(fireNow).start(t);

    return 1;
}
#else
long fire = 1;

int setupTimer(long t)
{
    return 0;
}
#endif

// Temp/Humidity Sensor
#define TEMP_DATA 6
DHT dht(TEMP_DATA, DHT11);

// DAC Chip
#define MCP_ADDR 0x60
MCP4725 MCP(MCP_ADDR);

// PIR Sensor
#define PIR_DATA 2
#define PIR_SHOW_LED 13

// Wave output indicator
#define PWM_LED 13

void setup()
{
  Serial.begin(115200);

  Wire.begin();
  // ESP32
  // MCP.begin(27, 26);
  // Wire.setClock(3400000);
  MCP.begin();
  Wire.setClock(800000);

  MCP.setValue(0);


  pinMode(PIR_DATA, INPUT);
  pinMode(PIR_SHOW_LED, OUTPUT);
  pinMode(PWM_LED, OUTPUT);

  analogWriteResolution(12);
  //  analogReadResolution(12);

  for (int d = 0; d < DEVICES; d++) {
    // Wake up
    lc.shutdown(d, false);

    // Med brighness
    lc.setIntensity(d, 12);

    // Fade brigthness
    // lc.setIntensity(d,1+d*d);

    // Clear
    lc.clearDisplay(d);
  }
}

void bigCounter()
{
    unsigned char big[SIZE];

    int i;

    for (i = 0; i < SIZE; i++)
    {
        big[i] = 0;
    }

    int haveTimer = setupTimer(1000000 / 25);

    // lc.setIntensity(0,15);

    long n = 0;

    while (1)
    {
        int i = 0;
        while (i < SIZE && (++big[i++] == 0))
            ;

        n++;

        if (fire)
        {
            for (int n = 0; n < DEVICES; n++)
            {
                fastShowCharN(SIZE, n, big);
            }

            if (haveTimer)
                fire = 0;
        }

        if (!haveTimer)
            delay(delaytime);
    }
}

void nowServing()
{
  int now = 100;

  int intensity = 12;

  do
  {
    char msg[60];

    sprintf(msg, "    ... Now serving>%3d", now);

    setDisplay(intensity);

    scrollString(SIZE, DEVICES, msg);

    int del = random(3) * 3 + 1;

    int inc = 1;

    if (random(10) <= 3)
    {
      inc += (random(3) + 1);
    }

    fadeDisplay(del * inc, intensity, 1, 80);

    now += inc;

    if (now > 999)
    {
      now = 42;
    }

  } while (true);
}

void phpIs()
{
  const char *whats[] = {
      "Shit",
      "ACE!",
      "Okay",
      "Duff"};

  int delayTime = 2000;

  int numWhats = sizeof(whats) / sizeof(*whats);

  char msg[64];

  sprintf(msg, "PHP is ...");
  scrollString(SIZE, DEVICES, msg);
  delay(delayTime);

  int what = random(numWhats);
  scrollString(SIZE, DEVICES, whats[what]);
  delay(delayTime);
}

void tempAndHumidity()
{
  const int oneSec = 1000;
  const int preReadDelay = 2 * oneSec;

  delay(preReadDelay);

  dht.read();

  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  char msg[64];

  if (isnan(temp) || isnan(humidity))
  {
    sprintf(msg, "Bad read!");
    scrollString(SIZE, DEVICES, msg);
  }
  else
  {
    sprintf(msg, "t=%2.0f\x7f", temp);
    scrollString(SIZE, DEVICES, msg);
    delay(oneSec);
    sprintf(msg, "h=%2.0f%%", humidity);
    scrollString(SIZE, DEVICES, msg);
  }
  delay(oneSec);
}

void animationTest()
{
  for (int i = 1; i < 20; i++)
  {
    char buf[20];

    sprintf(buf, " d=%dms ", i);
    scrollString(SIZE, DEVICES, buf);

    const char *msg = "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0d\x0e\x0f";
    int len = strlen(msg);
    const char *msg2 = "\x10\x11\x12\x13\x14\x15\x16\x17";

    int d = i * 10;
    int j = 1000 / (d * len);

    do
    {
      animateString(msg, d);

      animateString(msg2, d);

      j--;
    } while (j >= 0);
  }
}

void scrollAnimationLoop(int n)
{
  for (int l = 0; l <= n; l++)
  {
    scrollAnimation();
  }
}

#define SET_CELL(b, x, y) b[y] = b[y] | (1 << (SIZE - x - 1))
#define CLR_CELL(b, x, y) b[y] = b[y] & (~(1 << (SIZE - x - 1)) & 0xFF)
#define CELL_ISSET(b, x, y) ((b[y] & (1 << (SIZE - x - 1))) != 0)

int lifeBoardEmpty(byte b[8])
{
  for (int i = 0; i < SIZE; i++)
  {
    if (b[i])
      return 0;
  }

  return 1;
}

int lifeBoardCopy(byte from[8], byte to[8])
{
  for (int i = 0; i < SIZE; i++)
  {
    to[i] = from[i];
  }
}

int lifeBoardsSame(byte b1[8], byte b2[8])
{

  for (int i = 0; i < SIZE; i++)
  {
    if (b1[i] != b2[i])
      return 0;
  }

  return 1;
}

int lifeNeighbours(byte b[8], int x, int y)
{
  int res = 0;

  for (int r = y - 1; r < y + 2; r++)
  {
    for (int c = x - 1; c < x + 2; c++)
    {
      if ((r >= 0 && r < SIZE) && (c >= 0 && c < SIZE))
      {
        if (CELL_ISSET(b, c, r))
        {
          res++;
        }
      }
    }
  }

  if (CELL_ISSET(b, x, y))
  {
    res--;
  }

  return res;
}

void gameOfLife()
{
  byte b[8] = {0, 0, 0x70, 0, 0, 0x07, 0, 0};
  byte oldB[8];

  for (int i = 0; i < SIZE; i++)
  {
    // SET_CELL( b, i, i );

    b[i] = random(256);
  }

  fastShowChar(SIZE, b);

  delay(1000);

  int iterations = 100;
  int done = 0;

  while (!done && !lifeBoardEmpty(b) && iterations)
  {
    lifeBoardCopy(b, oldB);

    for (int y = 0; y < SIZE; y++)
    {
      for (int x = 0; x < SIZE; x++)
      {
        int nbs = lifeNeighbours(oldB, x, y);
        int live = CELL_ISSET(oldB, x, y);

        if (live)
        {
          if ((nbs < 2) || (nbs > 3))
          {
            CLR_CELL(b, x, y);
          }
        }
        else
        {
          if (nbs == 3)
          {
            SET_CELL(b, x, y);
          }
        }
      }
    }

    fastShowChar(SIZE, b);

    delay(60);

    done = lifeBoardsSame(b, oldB);

    iterations--;
  }

  delay(1000);

  int setCount = 0;

  for (int y = 0; y < SIZE; y++)
  {
    for (int x = 0; x < SIZE; x++)
    {
      if (CELL_ISSET(b, x, y))
      {
        setCount++;
      }
    }
  }

  char msg[65];
  sprintf(msg, "#=%d i=%d", setCount, 100 - iterations);
  scrollString(SIZE, DEVICES, msg);

  delay(1000);
}

void checkPir()
{
  int delayTime = 20;
  int pirRead;

  pirRead = digitalRead(PIR_DATA);

  if (pirRead == HIGH)
  {
    digitalWrite(PIR_SHOW_LED, HIGH);
  }
  else
  {
    digitalWrite(PIR_SHOW_LED, LOW);
  }

  if (pirRead == HIGH)
  {
    scrollString(SIZE, DEVICES, "...!!! STOP !!!...");
  }
  else
  {
    animateString("|/-\\", 200);
  }

  delay(delayTime);
}

// TODO: Separate out sine (table based) and others which can be specified via parameters
// TODO: Others being square, ramp, steps and triangle - parameters being frequency, duty cycle etc
// TODO: Also inverted option, modulation - see square wave

// Looks like DUE is limited to 133kHZ for a simple square wave at 50% duty cycle

const int FREQS = 0;
const int DELAYS = 1;

void playWave(int waveData[], int NUM_SAMPLES, int freq, int seconds, int mode)
{

  char msg[240];

  // sprintf(msg, "#SAMPLES = %d", NUM_SAMPLES);
  // Serial.println(msg);

  int pSecDelay = 1000000000 / (NUM_SAMPLES * freq);
  int uSecDelay = 1000000 / (NUM_SAMPLES * freq);

  int error = pSecDelay % 1000;

  const int PER_SAMPLE_ERROR = 0; // ps overhead

  if (mode == DELAYS)
  {
    uSecDelay = freq;
    if (uSecDelay == 0)
    {
      freq = 1000; // Fastest possible
    }
    else
    {
      freq = 1000000 / (NUM_SAMPLES * uSecDelay);
    }
  }

  // 10s of signal generation
  const int CYCLES = seconds * freq;

  // sprintf(msg, "MODE=%s: f=%d, d=%d us, #c=%d", mode == DELAYS ? "DELAY" : "FREQ", freq, uSecDelay, CYCLES);
  // Serial.println(msg);
  // sprintf(msg, "ERROR=%d, d=%ld ps", error, pSecDelay);
  // Serial.println(msg);

  int currError = 0;
  int extraDelay = 0;
  int adjusts = 0;

  for (int c = 0; c < CYCLES; c++)
  {
    analogWrite(DAC1, c % 2 == 0 ? 0xfff : 0);

    if ((c + 1) % freq == 0 || c == 0)
    {
      // NOTE: 12bit PWM
      int led_pwm = 4095;
      if (c != 0)
        led_pwm = 4095 - (4095 * ((c + 1) / freq) / seconds);
      analogWrite(PWM_LED, led_pwm);
    }

    for (int i = 0; i < NUM_SAMPLES; i++)
    {
      // Sawtooth - with sub-sampling
      //      int numRamps = 16;  // Or frequency, but with 'sub-sampling'
      //
      //      analogWrite(DAC0, (( i * numRamps ) % NUM_SAMPLES) * 0xfff / NUM_SAMPLES );  // Same speed as cycle as no sub-sampling

      // Square - the fastest. Need rate and duty cycle. Some cheeky modulation here though
      //        if ( i % 2 == 0 ) {
      //          analogWrite(DAC0, 0xfff - c/4);
      //        } else {
      //          analogWrite(DAC0, 0x0 + c/2);
      //        }

      // Sine - with sub-sampling. TODO: Figure out sub-sample values for 'higher' frequencies
      if (i % 5 == 0)
      {
        int d = waveData[i] / 2 + (4095 / 4 * 2); // Adds DC offset to output to keep LED forward biased
                                                  // waveData[i] / 4 + (4095 / 4 * 3) for BLUE LEDs

        analogWrite(DAC0, waveData[i]); // or d

        // Add this for XY plots of lissajous figures
        // MCP.setValue(waveData[(i+NUM_SAMPLES/4)%NUM_SAMPLES]);  // cos
      }

      if (currError >= 1000)
      {
        extraDelay = 1;
        currError -= 1000;
        adjusts++;
      }
      else if (currError <= -1000)
      {
        if (uSecDelay > 0)
        {
          extraDelay = -1;
        }
        else
        {
          extraDelay = 0;
        }
        currError += 1000;
        adjusts++;
      }
      else
      {
        extraDelay = 0;
      }

      delayMicroseconds(uSecDelay + extraDelay);

      currError += (error - PER_SAMPLE_ERROR);
    }
  }

  // sprintf(msg, "ERROR ADJUSTS=%d", adjusts);
  // Serial.println(msg);
}

int freqs[] = {1, 5, 10, 30, 50, 100}; //, 400, 750, 1000 };
int delays[] = {0, 1, 2, 4, 5, 10, 15, 25, 50, 75, 100};

void theWaves()
{
  const int NUM_FREQS = sizeof(freqs) / sizeof(int);

  for (int f = 0; f < NUM_FREQS; f++)
  {
    playWave(sineData, 1024, freqs[f], 10, FREQS);
    playWave(triangleData, 1024, freqs[f], 10, FREQS);
    playWave(squareData, 1024, freqs[f], 10, FREQS);
    playWave(rampData, 1024, freqs[f], 10, FREQS);
    playWave(impulseData, 1024, freqs[f], 10, FREQS);
  }
}

void sineWaves2()
{
  const int NUM_DELAYS = sizeof(delays) / sizeof(int);

  for (int d = 0; d < NUM_DELAYS; d++)
  {
    playWave(sineData, 1024, delays[d], 10, DELAYS);
  }
}

void loop()
{
  // theWaves();

  //  sineWaves2();

  // sineWave(3, 30);

  // checkPir();

  // testSpiral();

  bigCounter();

  // nowServing();

  // scrollString( SIZE, DEVICES, "Hello there Jenny, hello there Iman!, Yo POPS :)" );

  // tempAndHumidity();

  // scrollAnimationLoop( 10 );

  // phpIs();

  // animationTest();

  // gameOfLife();

  // writeArduinoOnMatrix();
}
